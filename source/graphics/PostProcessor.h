#include <string>

namespace liquid { namespace graphics {
#ifndef _POSTPROCESSOR_H
#define _POSTPROCESSOR_H

/**
 * \class PostProcessor
 *
 * \ingroup Graphics
 * \brief Defines an interface class for implementing PostProcessor effects on the game screen
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 24/04/2017
 *
 */

class Renderer;
class PostProcessor
{
public:
    /// PostProcessor Constructor
    PostProcessor();

    /** \brief PostProcessor Constructor
      * \param renderer Pointer to the Renderer used for this processor
      * \param name Name of this PostProcesssor
      */
    PostProcessor(Renderer* renderer, std::string name);

    /// PostProcessor Destructor
    ~PostProcessor();

    /// \brief Virtual function used to update the PostProcessors
    virtual void update();

    /// \brief Virtual function used to process any shaders
    virtual void process();

    /** \brief Sets the Enabled flag for this PostProcessor
      * \param flag Boolean flag to assign to mEnabled
      */
    void setEnabled(bool flag);

    /** \brief Sets the pointer to the Renderer to use
      * \param renderer Pointer to the Renderer
      */
    void setRendererPtr(Renderer* renderer);

    /** \brief Sets the name of this PostProcessor
      * \param name std::string value to assign to mName
      */
    void setName(std::string name);

    /** \brief Virtual function to set the vertex shader
      * \param vertShader std::string representation of the vertex shader
      */
    virtual void setVertShader(std::string vertShader);

    /** \brief Virtual function to set the vertex shader
      * \param fragShader std::string representation of the fragment shader
      */
    virtual void setFragShader(std::string fragShader);

    /// \return True if the PostProcessor can run, otherwise false
    const bool isEnabled() const;

    /// \return A pointer to the Renderer this PostProcessor belongs to
    const Renderer* getRenderer() const;

    /// \return Name of this PostProcessor as a std::string
    const std::string getName() const;

    /// \return Name and location of this PostProcessor objects vertex shader
    const std::string getVertShader() const;

    /// \return Name and location of this PostProcessor objects fragment shader
    const std::string getFragShader() const;

protected:
    bool        mEnabled;     ///< Denotes if this PostProcessor is active
    Renderer*   mRendererPtr; ///< Pointer to the Renderer the PostProcessor belongs to
    std::string mName;        ///< Name of the PostProcessor
    std::string mVertShader;  ///< Name and location of the vertex shader
    std::string mFragShader;  ///< Name and location of the fragment shader
};

#endif // _POSTPROCESSOR_H
}}
