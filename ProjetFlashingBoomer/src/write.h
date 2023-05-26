/*#ifndef _WRITE_H
#define _WRITE_H

/// \file write.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>

/// \class write
/// \brief classe contenant les differents éléments de la zone d'écriture

class write
{
    private:

        unsigned int WritingPosX, WritingPosY;
        int WritingWidth, WritingHeight;

    public:

        SDL_Rect srcRectWritingZone;

        /// \fn write()
        /// \brief constructeur par défaut de la classe write
        write();

        /// \fn write(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
        /// \brief constructeur par défaut de la classe write
        write(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

        /// \fn ~write()
        /// \brief destructeur par défaut de la classe write
        ~write();


        // ----> Accesseurs


        /// \fn unsigned int getWritingPosX() const
        /// \brief accesseur de la variable WritingPosX
        /// \return WritingPosX
        unsigned int getWritingPosX() const;

        /// \fn unsigned int getWritingPosY() const
        /// \brief accesseur de la variable WritingPosY
        /// \return WritingPosY
        unsigned int getWritingPosY() const;

        /// \fn int getWritingWidth() const
        /// \brief accesseur de la variable WritingWidth
        /// \return WritingWidth
        int getWritingWidth() const;

        /// \fn int getWritingHeight() const
        /// \brief accesseur de la variable WritingHeight
        /// \return WritingHeight
        int getWritingHeight() const;

        /// \fn SDL_Rect getsrcRectWritingZone() const;
        /// \brief accesseur du SDL_Rect 
        /// \return srcRectWritingZone
        SDL_Rect& getsrcRectWritingZone(); 


        // -----> Mutateurs


        /// \fn void setWritingPosX(unsigned int value)
        /// \brief mutateur de la variable WritingPosX
        /// \param value nouvelle valeur de la variable
        void setWritingPosX(unsigned int value);

        /// \fn void setWritingPosY(unsigned int value)
        /// \brief mutateur de la variable WritingPosY
        /// \param value nouvelle valeur de la variable
        void setWritingPosY(unsigned int value);

        /// \fn void setWritingWidth(int value)
        /// \brief mutateur de la variable WritingWidth
        /// \param value nouvelle valeur de la variable
        void setWritingWidth(int value);

        /// \fn void setWritingHeight(int value)
        /// \brief mutateur de la variable WritingHeight
        /// \param value nouvelle valeur de la variable
        void setWritingHeight(int value);

};

#endif
*/