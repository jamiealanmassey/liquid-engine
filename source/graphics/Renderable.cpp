#include "Renderable.h"
#include "../common/ResourceManager.h"
#include "../utilities/FileName.h"
#include "../utilities/Vectors.h"
#include "../utilities/DeltaTime.h"

#include <fstream>
#include <PugiXML/pugixml.hpp>

Renderable::Renderable(std::string texture, int32_t scene_depth) :
	m_Textured(false),
	m_Animated(false),
	m_Shaded(false),
	m_DualRender(true),
	m_CentreOrigin(true),
	m_Active(true),
	m_TexturePtr(nullptr),
	m_ShaderPtr(nullptr),
	m_TexturePath(""),
	m_AnimationPath(""),
	m_ShaderVertPath(""),
	m_ShaderFragPath(""),
	m_FacingDir(MAT_FACING_DIR),
	f_RenderOverride(nullptr)
{
	// If there is a texture being passed call to loadTexture(string)
	if (texture != "")
		loadTexture(texture);

	// Assign the Scene Depth for rendering
	m_SceneDepth = scene_depth;
}

Renderable::~Renderable()
{
}

void Renderable::update()
{
	// First make sure the renderable is active before updating
	if (!m_Active)
		return;

	// First check if the renderable is shaded, if it is then we want to pass some
	// parameters for the shader
	if (checkShaded())
	{
		m_ShaderPtr->setParameter("r_delta", Delta);
		m_ShaderPtr->setParameter("r_time", Time);
		m_ShaderPtr->setParameter("r_texture", *m_TexturePtr);
	}

	// Next if the Renderable is animated we want to update the animation
	if (checkAnimated())
	{
		// Make sure we update the animation tick if we haven't hit end of frame
		if (m_AnimationTable[m_CurrentAnimation][m_CurrentFrame].delay >= 0.0f)
			m_AnimationTick += Delta;

		// Provided the animation tick counter has surpassed the delay we want to update the
		// current frame
		if (m_AnimationTick > m_AnimationTable[m_CurrentAnimation][m_CurrentFrame].delay)
		{
			// Update the animation tick variable
			m_AnimationTick -= m_AnimationTable[m_CurrentAnimation][m_CurrentFrame].delay;

			// Based on the animation mode progress the frame
			if (m_AnimationMode == eAnimationMode::DEFAULT)
				m_CurrentFrame++;
			else if (m_AnimationMode == eAnimationMode::ONCE)
				m_CurrentFrame++;
			else if (m_AnimationMode == eAnimationMode::REVERSE)
				m_CurrentFrame--;
			else if (m_AnimationMode == eAnimationMode::PINGPONG)
			{
				if (m_AnimationDir == eAnimationDir::FORWARD)
					m_CurrentFrame++;
				else
					m_CurrentFrame--;
			}

			// Make sure to check and update constraints
			if (m_AnimationMode == eAnimationMode::DEFAULT && m_CurrentFrame > m_EndFrame)
				m_CurrentFrame = m_StartFrame;
			else if (m_AnimationMode == eAnimationMode::REVERSE && m_CurrentFrame < m_StartFrame)
				m_CurrentFrame = m_EndFrame;
			else if (m_AnimationMode == eAnimationMode::ONCE && m_CurrentFrame > m_EndFrame)
			{
				m_CurrentFrame = m_EndFrame;

				if (m_DefaultAnimation != "")
					changeAnimation(m_DefaultAnimation, m_DefaultStartFrame, m_DefaultEndFrame);

				return;
			}
			else if (m_AnimationMode == eAnimationMode::PINGPONG)
			{
				if (m_AnimationDir == eAnimationDir::FORWARD && m_CurrentFrame > m_EndFrame)
					m_AnimationDir = eAnimationDir::BACKWARD;
				else if (m_AnimationDir == eAnimationDir::BACKWARD && m_CurrentFrame < m_StartFrame)
					m_AnimationDir = eAnimationDir::FORWARD;
			}

			// Finally update the frame
			updateFrame(m_AnimationTable[m_CurrentAnimation][m_CurrentFrame]);
		}
	}
}

void Renderable::render(sf::RenderTarget& target)
{
	// First make sure the renderable is active before rendering
	if (!m_Active)
		return;

	// If the target is textured and there is no override function then draw as usual,
	// however if a render override function exists go to that
	if(m_DualRender)
	{
		if (m_Textured)
			target.draw(*this, m_RenderStates);

		if (f_RenderOverride)
			f_RenderOverride(this, target);
	}
	else
	{
		if (f_RenderOverride)
			f_RenderOverride(this, target);
		else if(m_Textured)
			target.draw(*this, m_RenderStates);
	}
}

void Renderable::loadTexture(std::string texture)
{
	// Switch texture state and assign path
	m_Textured = true;
	m_TexturePath = texture;

	// Create a new texture and load it from the file
	m_TexturePtr = ResourceManager::instance().lookupTexture(texture);

	// Set the texture and assign an origin
	setTexture(*m_TexturePtr);

	// Capture texture dimensions
	m_Dimensions	 = sf::Vector2f(m_TexturePtr->getSize());
	m_DimensionsInit = sf::Vector2f(m_TexturePtr->getSize());
}

void Renderable::loadAnimation(std::string animation_path)
{
	// Attempt to create an XML instance of the document
	pugi::xml_document animation_file;
	if (!animation_file.load_file(animation_path.c_str()))
		return;

	// Update the animated flag and assign the path
	m_Animated = true;
	m_AnimationPath = animation_path;

	// Locate the root of the document and iterate through each node sampling data
	// to be used as the animation frame data in the Renderable
	pugi::xml_node root = animation_file.child("AnimationData");
	for (pugi::xml_node_iterator nodes = root.begin(); nodes != root.end(); ++nodes)
	{
		// Sample the name from the node and update the animation indexer
		std::string name = nodes->attribute("Name").as_string();
		m_AnimationIndexer[m_AnimationTable.size()] = name;

		// Iterate over each frame node for the data about each frame of the animation
		for (pugi::xml_node_iterator frames = nodes->begin(); frames != nodes->end(); ++frames)
		{
			// Produce a new frame instance
			AnimationFrame frame;

			// Assign extracted data from the frame
			frame.local_x = frames->child("LocalX").attribute("Value").as_int();
			frame.local_y = frames->child("LocalY").attribute("Value").as_int();
			frame.width = frames->child("Width").attribute("Value").as_int();
			frame.height = frames->child("Height").attribute("Value").as_int();
			frame.delay = frames->child("Time").attribute("Value").as_float();

			// Add new frame data to the animation table
			m_AnimationTable[name].push_back(frame);
		}
	}

	// Produce default animation variables
	m_AnimationMode		= eAnimationMode::DEFAULT;
	m_AnimationDir		= eAnimationDir::FORWARD;
	m_DefaultAnimation	= "";
	m_CurrentAnimation	= m_AnimationIndexer[0];
	m_DefaultStartFrame = -1;
	m_DefaultEndFrame	= -1;
	m_CurrentFrame		= 0;
	m_StartFrame		= 0;
	m_EndFrame			= (m_AnimationTable[m_CurrentAnimation].size() - 1);

	// Update for first frame
	updateFrame(getAnimation(0)[0]);
}

void Renderable::loadShader(std::string fragment_path, std::string vertex_path)
{
	// Make sure valid paths have been passed
	if (fragment_path == "" || vertex_path == "")
		return;

	// Create a new instance of the shader and load it from memory with the use
	// of our extended helper function
	m_ShaderPtr = new sf::Shader;
	m_ShaderPtr->loadFromMemory(processShader(vertex_path, sf::Shader::Vertex),
		processShader(fragment_path, sf::Shader::Fragment));

	// Assign frag and vert paths
	m_ShaderFragPath = fragment_path;
	m_ShaderVertPath = vertex_path;

	// Update shaded flag and pass shader to RenderStates
	m_Shaded			  = true;
	m_RenderStates.shader = m_ShaderPtr;
}

std::string Renderable::processShader(std::string file, sf::Shader::Type type)
{
	// PRE-DEFINED GLOBAL SHADER VARIABLES
	static const char shared_globals[] =
	{
		"uniform float r_delta;\n"
		"uniform float r_time;\n"
	};

	static const char frag_globals[] =
	{
		"uniform sampler2D r_texture;\n"
	};

	// Manually read in the source code
	std::ifstream stream(file, std::ios_base::in);
	if (!stream.is_open())
		return "";

	std::string code = "";
	while (!stream.eof())
	{
		std::string line = "";
		getline(stream, line);
		code += line + "\n";
	}

	// Find newline before main function
	size_t main_pos = code.find("main");
	main_pos = code.substr(0, main_pos).find_last_of('\n');

	// Check for carriage return and start of file
	if (main_pos == std::string::npos)
		main_pos = 0;
	else if (code[main_pos - 1] == '\r') // Should be safe to do
		main_pos--;

	// Insert pre-defined uniforms
	code.insert(main_pos, shared_globals);

	if (type == sf::Shader::Fragment)
		code.insert(main_pos, frag_globals);

	// Close file, return altered code
	stream.close();
	return code;
}

void Renderable::changeAnimation(std::string name, int32_t begin, int32_t end)
{
	if (m_AnimationTable.find(name) == m_AnimationTable.end())
		return;

	// Store the new mode, a flag for whether the bounds are unique or default etc.
	eAnimationMode new_mode	   = eAnimationMode::DEFAULT;
	bool default_bounds		   = (begin == -1 && end == -1);
	int32_t split_string	   = name.find_first_of(":");
	std::string animation_name = name.substr(0, split_string);
	std::string animation_mode;

	// Split modifier if it exists
	if (split_string != -1)
	{
		animation_mode = name.substr(split_string + 1);

		if (animation_mode == "loop")
			new_mode = eAnimationMode::DEFAULT;
		else if (animation_mode == "once")
			new_mode = eAnimationMode::ONCE;
		else if (animation_mode == "pingpong")
			new_mode = eAnimationMode::PINGPONG;
		else if (animation_mode == "reverse")
			new_mode = eAnimationMode::REVERSE;
	}
	else
		animation_mode = "";

	// If there are no specified bounds then set the begin and end frames
	// to the first and last frames of the actual animation
	if (default_bounds)
	{
		begin = 0;
		end   = getAnimation(animation_name).size() - 1;
	}

	// If the animation passed is the same as the current one and the given begin and end
	// frames are the same as the currently set ones then we do not wish to change the animation
	// mid-flow
	if (animation_name == m_CurrentAnimation && (begin == m_StartFrame && end == m_EndFrame))
		return;

	// Update frame bounds
	m_StartFrame = begin;
	m_EndFrame = end;

	// Change animtion and default current frame
	m_CurrentAnimation = animation_name;
	m_CurrentFrame = begin;

	// If an Animation Mode was also passed update it
	if (animation_mode != "")
		changeAnimationMode(new_mode);
	else
		changeAnimationMode(eAnimationMode::DEFAULT);

	// First frame
	updateFrame(m_AnimationTable[m_CurrentAnimation][m_CurrentFrame]);
}

void Renderable::changeDefaultAnimation(std::string name, int32_t begin, int32_t end)
{
	// Don't check bounds, don't split animation string!
	// These are just passed on to changeAnimation(...)
	m_DefaultStartFrame = begin;
	m_DefaultEndFrame = end;
	m_DefaultAnimation = name;
}

void Renderable::changeAnimationMode(eAnimationMode mode)
{
	// Simply assign the new animation mode
	m_AnimationMode = mode;
}

void Renderable::updateFrame(AnimationFrame frame)
{
	// Re-capture texture with frame data
	setTextureRect(sf::IntRect(frame.local_x, frame.local_y, frame.width, frame.height));

	// Update dimensions
	m_Dimensions.x = (float)frame.width;
	m_Dimensions.y = (float)frame.height;
	
	if (m_CentreOrigin)
		setOrigin(m_Dimensions / 2.f);

	// Change rotation if needed
	if (m_Rotation != 0.f)
		setRotation(m_Rotation);
}

void Renderable::updateRotation(float angle)
{
	// Store the new angle and pass it to SFML
	m_Rotation = angle;
	setRotation(m_Rotation);

	// 
	float last_x   = m_Dimensions.x;
	m_Dimensions.x = m_Dimensions.y;
	m_Dimensions.y = last_x;

	// Updating facing direction
	float rad     = (float)(m_Rotation * PI / 180.f);
	m_FacingDir.x = cos(rad) * MAT_FACING_DIR.x - sin(rad) * MAT_FACING_DIR.y;
	m_FacingDir.y = sin(rad) * MAT_FACING_DIR.x + cos(rad) * MAT_FACING_DIR.y;
}

void Renderable::clipSprite(sf::IntRect bounds)
{
	// Update the texture rect and sample our new dimensions
	setTextureRect(bounds);
	m_Dimensions.x = (float)bounds.width;
	m_Dimensions.y = (float)bounds.height;
}

float Renderable::faceTarget(const sf::Vector2f& v)
{
	// Compute Angle
	float angle = getAngle(MAT_FACING_DIR, (v - getPosition()));

	// Update the Rotation
	updateRotation((float)(angle * 180.0f / PI));
	return m_Rotation;
}

void Renderable::setBlendMode(sf::BlendMode mode)
{
	// Change the blending mode in RenderStates
	m_RenderStates.blendMode = mode;
}

void Renderable::setAlpha(uint8_t alpha)
{
	// Sample the colour and apply the alpha
	sf::Color c = getColor();
	c.a = alpha;
	setColor(c);
}

void Renderable::setDimensions(const sf::Vector2f& v)
{
	// Update dimensions variable
	m_Dimensions.x = v.x;
	m_Dimensions.y = v.y;
}

void Renderable::setDimensionsInit(const sf::Vector2f& v)
{
	// Update dimensions initial variable (be careful!)
	m_DimensionsInit.x = v.x;
	m_DimensionsInit.y = v.y;
}

Renderable::AnimationFrames& Renderable::getAnimation(int32_t index)
{
	// Use AnimationIndexer to find Animation
	return getAnimation(m_AnimationIndexer[index]);
}

Renderable::AnimationFrames& Renderable::getAnimation(std::string name)
{
	// Make sure animation exists
	if (m_AnimationTable.find(name) != m_AnimationTable.end())
		return m_AnimationTable[name];

	// If not return an empty vector
	return AnimationFrames();
}
