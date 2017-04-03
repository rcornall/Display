#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "OpenGL");

    // Set Orthographic
    auto width = static_cast<float>(window.getSize().x);
    auto height = static_cast<float>(window.getSize().y);
    auto a = 2.f / width;
    std::cout << a << width << std::endl;
    auto b = 2.f / height;
    std::cout << a << std::endl;
    std::vector<float> matrix =
    {
         a , 0, 0, 0,
         0, -b, 0, 0,
         0,  0, 1, 0,
        -1,  1, 0, 1
    };

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(matrix.data());

    // Initialize vertices:
    std::vector<float> vertices =
    {
        0,     0,
        0,     height,
        width, height,
        width, 0
    };

    // Initialize colors
    std::vector<float> colors =
    {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        0, 1, 1
    };

    // Initialize texture virtice
    std::vector<float> texCoord =
    {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };

    // Create texture: simple chess board 8x8
    auto numRows = 8u;
    auto numCols = 8u;
    auto character = 172u;
    auto remain = 255u - character;
    std::vector<unsigned char> texture(numCols * numRows);
    for (auto i = 0u; i < texture.size(); ++i)
        texture[i] = ((i + (i / numCols)) % 2) * remain + character;

    // Upload to GPU texture
    unsigned textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, numCols, numRows, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texture.data());

    // Initialize clear colors
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Activate necessary states
    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, vertices.data());
    glColorPointer(3, GL_FLOAT, 0, colors.data());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoord.data());

    while (window.isOpen())
    {
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            if (windowEvent.type == sf::Event::Closed)
                window.close();
        }

        // render
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_QUADS, 0, 4);

        window.display();
    }
}
