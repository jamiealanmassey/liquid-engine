#ifndef _RENDERABLE_H
#define _RENDERABLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#define PI 3.14159265
#define MAT_FACING_DIR sf::Vector2f(-1.0f, 0.0f)

struct AnimationFrame
{
	int32_t local_x;
	int32_t local_y;
	int32_t width;
	int32_t height;
	float   delay;
};

class Renderable : public sf::Sprite
{
public:
	enum eAnimationMode
	{
		DEFAULT  = 0,
		ONCE	 = 1,
		PINGPONG = 2,
		REVERSE  = 3,
	};

	enum eAnimationDir
	{
		FORWARD  = 0,
		BACKWARD = 1,
	};

	enum eRenderableType
	{
		WORLD = 0,
		UI	  = 1,
	};

public:
	typedef std::vector<AnimationFrame>			   AnimationFrames;
	typedef std::map<std::string, AnimationFrames> AnimationTable;
	typedef std::map<int32_t, std::string>		   AnimationIndexer;

public:
	Renderable(std::string texture, int32_t scene_depth = 1);
	~Renderable();

	/* Core renderable functions */
	void update();
	void render(sf::RenderTarget& target);

	/* Loading functions */
	void loadTexture(std::string texture);
	void loadAnimation(std::string animation_path);
	
	/* Shader functions */
	void		loadShader(std::string fragment_path, std::string vertex_path);
	std::string processShader(std::string file, sf::Shader::Type type);

	/* Animation specific control functions */
	void changeAnimation(std::string name, int32_t begin = -1, int32_t end = -1);
	void changeDefaultAnimation(std::string name, int32_t begin = -1, int32_t end = -1);
	void changeAnimationMode(eAnimationMode mode);

	/* Animation updating functions */
	void updateFrame(AnimationFrame frame);
	void updateRotation(float angle);

	/* Special helper proceses */
	void  clipSprite(sf::IntRect bounds);
	float faceTarget(const sf::Vector2f& v);

	/* Setter functions */
	void setBlendMode(sf::BlendMode mode);
	void setAlpha(uint8_t alpha);
	void setDimensions(const sf::Vector2f& v);
	void setDimensionsInit(const sf::Vector2f& v);

	/* Setter functions */
	void setDualRender(bool flag)				 { m_DualRender = true;		}
	void setRenderableType(eRenderableType type) { m_RenderableType = type; }
	void setCentreOrigin(bool flag)				 { m_CentreOrigin = flag;   }
	void setActive(bool flag)					 { m_Active = flag;			}

	/* Helper functions to check if components exist */
	bool checkTextured() { return m_Textured;	  }
	bool checkAnimated() { return m_Animated;	  }
	bool checkShaded()   { return m_Shaded;		  }
	bool checkCentred()  { return m_CentreOrigin; }

	/* Getters for stored data */
	int32_t		 getSceneDepth() const { return m_SceneDepth; }
	sf::Texture* getTexturePtr() const { return m_TexturePtr; }
	sf::Shader*  getShaderPtr()  const { return m_ShaderPtr;  }

	/* Getters for general path information */
	std::string getTexturePath()	const { return m_TexturePath;	 }
	std::string getAnimationPath()  const { return m_AnimationPath;  }
	std::string getShaderVertPath() const { return m_ShaderVertPath; }
	std::string getShaderFragPath() const { return m_ShaderFragPath; }

	/* Getter Functions */
	sf::Vector2f	getDimensions()		const { return m_Dimensions;	 }
	sf::Vector2f	getDimensionsInit() const { return m_DimensionsInit; }
	eRenderableType getRenderableType() const { return m_RenderableType; }

	/* Getters for animations */
	AnimationFrames& getAnimation(int32_t index);
	AnimationFrames& getAnimation(std::string name);

	/* Getters for frame data */
	int32_t getDefaultStartFrame() const { return m_DefaultStartFrame; }
	int32_t getDefaultEndFrame()   const { return m_DefaultEndFrame;   }
	int32_t getCurrentFrame()	   const { return m_CurrentFrame;	   }
	int32_t getStartFrame()		   const { return m_StartFrame;		   }
	int32_t getEndFrame()		   const { return m_EndFrame;		   }

public:
	std::function<void(Renderable*, sf::RenderTarget&)> f_RenderOverride; ///< Function callback to override standard rendering

protected:
	bool			 m_Textured;	   ///< Flag to denote whether the renderable is textured
	bool			 m_Animated;	   ///< Flag to denote whether the renderable is animated 
	bool			 m_Shaded;		   ///< Flag to denote whether the renderable has shaders
	bool			 m_DualRender;	   ///< Flag to denote whether to render sprite and override
	bool			 m_CentreOrigin;   ///< Flag to denote whether the origin of the entity should be the centre
	bool			 m_Active;		   ///< Flag to denote whether to render/update renderable
	float			 m_Rotation;	   ///< Rotation of the Renderable to screen
	int32_t			 m_SceneDepth;	   ///< Stores the Scene Depth of the renderable for rendering order
	sf::Texture*	 m_TexturePtr;	   ///< Pointer to the stored texture being used
	sf::Shader*		 m_ShaderPtr;	   ///< Pointer to the stored shader being used
	sf::RenderStates m_RenderStates;   ///< Render States of the renderable
	std::string		 m_TexturePath;	   ///< Path to the texture being used
	std::string		 m_AnimationPath;  ///< Path to the animation being used
	std::string		 m_ShaderVertPath; ///< Path to the vertex shader
	std::string		 m_ShaderFragPath; ///< Path to the fragment shader
	sf::Vector2f	 m_Dimensions;	   ///< Dimensions of the loaded graphic
	sf::Vector2f	 m_DimensionsInit; ///< Dimensions that the graphic loaded with
	sf::Vector2f	 m_FacingDir;	   ///< Direction that the graphic is facing
	eRenderableType  m_RenderableType; ///< Enumerator for renderable type

private:
	AnimationTable	 m_AnimationTable;	  ///< Table of AnimationFrames with string identifiers
	AnimationIndexer m_AnimationIndexer;  ///< Indexes the animation table string identifiers
	eAnimationMode	 m_AnimationMode;	  ///< Stores the current animation mode
	eAnimationDir	 m_AnimationDir;	  ///< Stores the progression direction of the animation
	std::string		 m_DefaultAnimation;  ///< String identifier for the default animation
	std::string		 m_CurrentAnimation;  ///< String identifier for the animation being played
	int32_t			 m_DefaultStartFrame; ///< Default start frame
	int32_t			 m_DefaultEndFrame;	  ///< Default end frame
	int32_t			 m_CurrentFrame;	  ///< Current frame of the animation
	int32_t			 m_StartFrame;		  ///< Capped starting frame of the animation
	int32_t			 m_EndFrame;		  ///< Capped ending frame of the animation
	float			 m_AnimationTick;	  ///< Time passed for animation
};

#endif // _RENDERABLE_H
