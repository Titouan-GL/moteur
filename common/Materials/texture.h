#pragma once


#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "external/stb_image/stb_image.h"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <cstring>



struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    Color(unsigned char a, unsigned char b, unsigned char c) // construction par listes d'initialisation
        : r(a),
        g(b),
        b(c)
        {}
};

class Texture {
// https://learnopengl.com/Getting-started/Textures

protected:

    std::vector< unsigned char > data;
    GLuint _texture_id;
    bool __synchronized = false;

    Color getPixel(size_t u, size_t v) const;

    void unsynchronize(){
        
        if (!__synchronized) return;

        glDeleteTextures(1, &_texture_id);

        __synchronized = false;
    }

public:

    int width, height;
    int nbChannels;
    bool sharp = false;

    Texture(const std::string path, bool isPixelArt = false){
        loadTexture(path);
        sharp = isPixelArt;
    }

    // Constructeur par copie, permet de recréer une copie GPU de la texture à la copie
    // pour éviter les effets de bord.
    Texture(const Texture & other) : data(other.data),
    width(other.width),
    height(other.height),
    nbChannels(other.nbChannels)
    {
        sharp = other.sharp;
        __synchronized = false;
        if (!data.empty())
            synchronize();
    }

    Texture() = default;
    Texture(Texture &&) = default;
    ~Texture(){if (__synchronized) unsynchronize();}

    void loadTexture(const std::string path){
        constexpr int CHANNELS = 3;
        // on force toutes les textures à être en 3 canaux
        unsigned char * new_data = stbi_load(path.c_str(), &width, &height, &nbChannels, CHANNELS);
        if (!new_data){
            std::cout << "[Texture] Problème du chargement de la texture à " << path << " (impossible de charger les données)" << std::endl;
            return;
        }

        data.resize(width * height * CHANNELS);
        memcpy(data.data(), new_data, width * height * CHANNELS);
        stbi_image_free(new_data);
        synchronize();
    }

    Color getPixelSafe(size_t u, size_t v) const;

    Color getPixelSafe(float x, float y) const;

    Color operator() (size_t i, size_t j) {

        return getPixelSafe(i, j);
    }

    void setPixelArt(bool p){
        sharp = p;
        std::cout<< sharp << std::endl;
    }

    // permet de créer une texture d'un seul pixel avec couleur donnée
    static Texture createFlatColorTexture(const Color & val){
        Texture t;
        t.data = {val.r, val.g, val.b};
        t.width = t.height = 1;
        t.nbChannels = 3;
        t.synchronize();
        return t;
    }

    GLuint getTextureId() const{ return _texture_id;};


    /*////////
        TP
    /*////////
    void synchronize(){
        
        if (__synchronized) return; // pour pas resynchroniser

        // on génère une nouvelle texture : glGenTextures( <quantité>, <adresse de l'entier où mettre l'identifiant ('handle')> )
        glGenTextures(1, &_texture_id);

        // on bind la texture générée : glBindTexture(<type> = GL_TEXTURE_2D, <handle>)
        glBindTexture(GL_TEXTURE_2D, _texture_id);

        // déclarer les options de la texture qu'on vient de bind : glTexParameteri(GL_TEXTURE_2D, <option>, <valeur>);
        
        // Options de répétition (quand les UV dépassent du range standard)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Question 2.3.1 & Question 2.3.2
        // (Adaptez les options suivantes pour répondre aux deux questions.)
        if(sharp){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // quand loin (texture rétrécit)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // quand proche (texture grandit)
        }
        else{
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // quand loin (texture rétrécit)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // quand proche (texture grandit)
        }

        // On envoie les données de texture (au format GL_RGB) : glTexImage2D( ... )
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,  data.data());

        // appeler la génération de mipmaps
        glGenerateMipmap(GL_TEXTURE_2D); 
    }


    void bind(GLuint slot = 0) const {

        // Question 2.2
        // Activez le slot de texture de l'indice correspondant avec glActiveTexture
        // puis bindez la texture au point d'attache GL_TEXTURE_2D avec glBindTexture
        glActiveTexture(GL_TEXTURE0+slot);
        glBindTexture(GL_TEXTURE_2D, _texture_id);
    }
};
