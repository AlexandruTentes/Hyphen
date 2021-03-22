#include "../../../lib/GraphicEngine/Buffer/FrameBuffer.h"

namespace Hyphen
{
    void FrameBuffer::generate_buffers()
    {
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        //TEMP
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR: COULD NOT COMPLETE FRAMEBUFFER" << "\n";

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        status = true;
    }

    void FrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    }

    void FrameBuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    unsigned int FrameBuffer::get_id()
    {
        return fbo;
    }

    unsigned int FrameBuffer::get_tex()
    {
        return tex;
    }

    bool FrameBuffer::get_status()
    {
        return status;
    }

    void FrameBuffer::remove()
    {
        glDeleteTextures(1, &tex);
        glDeleteRenderbuffers(1, &rbo);
        glDeleteFramebuffers(1, &fbo);
        status = false;
    }
}