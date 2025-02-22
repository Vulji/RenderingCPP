#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

int main()
{

    // Initialisation
    gl::init("TPs de Rendering"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut
    glEnable(GL_DEPTH_TEST);
    gl::framebuffer_aspect_ratio();
    auto camera = gl::Camera{};
    
    auto render_target = gl::RenderTarget{gl::RenderTarget_Descriptor{
        .width          = gl::framebuffer_width_in_pixels(),
        .height         = gl::framebuffer_height_in_pixels(),
        .color_textures = {
            gl::ColorAttachment_Descriptor{
                .format  = gl::InternalFormat_Color::RGBA8,
                .options = {
                    .minification_filter  = gl::Filter::NearestNeighbour, // On va toujours afficher la texture à la taille de l'écran,
                    .magnification_filter = gl::Filter::NearestNeighbour, // donc les filtres n'auront pas d'effet. Tant qu'à faire on choisit le moins coûteux.
                    .wrap_x               = gl::Wrap::ClampToEdge,
                    .wrap_y               = gl::Wrap::ClampToEdge,
                },
            },
        },
        .depth_stencil_texture = gl::DepthStencilAttachment_Descriptor{
            .format  = gl::InternalFormat_DepthStencil::Depth32F,
            .options = {
                .minification_filter  = gl::Filter::NearestNeighbour,
                .magnification_filter = gl::Filter::NearestNeighbour,
                .wrap_x               = gl::Wrap::ClampToEdge,
                .wrap_y               = gl::Wrap::ClampToEdge,
            },
        },
    }};
    
    
    gl::set_events_callbacks({
        camera.events_callbacks(),
        {.on_framebuffer_resized = [&](gl::FramebufferResizedEvent const& e) {
            if(e.width_in_pixels != 0 && e.height_in_pixels != 0) // OpenGL crash si on tente de faire une render target avec une taille de 0
                render_target.resize(e.width_in_pixels, e.height_in_pixels);
        }},
    });


    auto const shader = gl::Shader{{
    .vertex   = gl::ShaderSource::File{"res/vertex.glsl"},
    .fragment = gl::ShaderSource::File{"res/fragment.glsl"},
}};

auto const screen_shader = gl::Shader{{
    .vertex   = gl::ShaderSource::File{"res/screen_vertex.glsl"},
    .fragment = gl::ShaderSource::File{"res/screen_fragment.glsl"},
}};


auto const texture = gl::Texture{
    gl::TextureSource::File{ // Peut être un fichier, ou directement un tableau de pixels
        .path           = "res/texture.png",
        .flip_y         = true, // Il n'y a pas de convention universelle sur la direction de l'axe Y. Les fichiers (.png, .jpeg) utilisent souvent une direction différente de celle attendue par OpenGL. Ce booléen flip_y est là pour inverser la texture si jamais elle n'apparaît pas dans le bon sens.
        .texture_format = gl::InternalFormat::RGBA8, // Format dans lequel la texture sera stockée. On pourrait par exemple utiliser RGBA16 si on voulait 16 bits par canal de couleur au lieu de 8. (Mais ça ne sert à rien dans notre cas car notre fichier ne contient que 8 bits par canal, donc on ne gagnerait pas de précision). On pourrait aussi stocker en RGB8 si on ne voulait pas de canal alpha. On utilise aussi parfois des textures avec un seul canal (R8) pour des usages spécifiques.
    },
    gl::TextureOptions{
        .minification_filter  = gl::Filter::Linear, // Comment on va moyenner les pixels quand on voit l'image de loin ?
        .magnification_filter = gl::Filter::Linear, // Comment on va interpoler entre les pixels quand on zoom dans l'image ?
        .wrap_x               = gl::Wrap::MirroredRepeat,   // Quelle couleur va-t-on lire si jamais on essaye de lire en dehors de la texture ?
        .wrap_y               = gl::Wrap::MirroredRepeat,   // Idem, mais sur l'axe Y. En général on met le même wrap mode sur les deux axes.
    }
};


   auto const rectangle_mesh = gl::Mesh{{
    .vertex_buffers = {{
        .layout = {gl::VertexAttribute::Position3D{0},gl::VertexAttribute::UV{1}},
        .data   = {
            -1.f, -1.f, +1.f, 0.f, 0.f,
            +1.f, -1.f, +1.f, 1.f, 0.f,
            +1.f, +1.f, +1.f, 1.f, 1.f,
            -1.f, +1.f, +1.f, 0.f, 1.f,

            -1.f, -1.f, -1.f, 0.f, 0.f,
            +1.f, -1.f, -1.f, 1.f, 0.f,
            +1.f, +1.f, -1.f, 1.f, 1.f,
            -1.f, +1.f, -1.f, 0.f, 1.f,

            -1.f, -1.f, -1.f, 0.f, 0.f,
            -1.f, -1.f, +1.f, 1.f, 0.f,
            -1.f, +1.f, +1.f, 1.f, 1.f,
            -1.f, +1.f, -1.f, 0.f, 1.f,

            +1.f, -1.f, -1.f, 0.f, 0.f,
            +1.f, -1.f, +1.f, 1.f, 0.f,
            +1.f, +1.f, +1.f, 1.f, 1.f,
            +1.f, +1.f, -1.f, 0.f, 1.f,

            -1.f, +1.f, +1.f, 0.f, 0.f,
            +1.f, +1.f, +1.f, 1.f, 0.f,
            +1.f, +1.f, -1.f, 1.f, 1.f,
            -1.f, +1.f, -1.f, 0.f, 1.f,

            -1.f, -1.f, +1.f, 0.f, 0.f,
            +1.f, -1.f, +1.f, 1.f, 0.f,
            +1.f, -1.f, -1.f, 1.f, 1.f,
            -1.f, -1.f, -1.f, 0.f, 1.f
        },
    }},
    .index_buffer   = {

      0, 1, 2, 2, 3, 0,

      4, 5, 6, 6, 7, 4,

      8, 9, 10, 10, 11, 8,

      12, 13, 14, 14, 15, 12,

      16, 17, 18, 18, 19, 16,

      20, 21, 22, 22, 23, 20,
    },
}};

    while (gl::window_is_open())
    {
        render_target.render([&]() {
            glClearColor(1.f, 0.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            shader.bind();
            shader.set_uniform("aspect_ratio", gl::framebuffer_aspect_ratio());
            shader.set_uniform("time_addition", gl::time_in_seconds());
            shader.set_uniform("my_texture", texture);
    
            glm::mat4 const view_matrix = camera.view_matrix();
            glm::mat4 const projection_matrix = glm::infinitePerspective(1.f, gl::framebuffer_aspect_ratio(), 0.001f);
            shader.set_uniform("view_projection_matrix", projection_matrix * view_matrix);
    
            glm::mat4 const rotation = glm::rotate(glm::mat4{1.f}, gl::time_in_seconds(), glm::vec3{0.f, 0.f, 1.f});
            glm::mat4 const translation = glm::translate(glm::mat4{1.f}, glm::vec3{0.f, 1.f, 0.f});
            shader.set_uniform("model_matrix", translation * rotation);
    
            rectangle_mesh.draw();

        
    });

    screen_shader.bind();

        auto const screen_mesh = gl::Mesh{{
            .vertex_buffers = {{
                .layout = {gl::VertexAttribute::Position2D{0}, gl::VertexAttribute::UV{1}},
                .data   = {
                    -1.f, -1.f, 0.f, 0.f,
                     1.f, -1.f, 1.f, 0.f,
                     1.f,  1.f, 1.f, 1.f,
                    -1.f,  1.f, 0.f, 1.f
                },
            }},
            .index_buffer = {0, 1, 2, 2, 3, 0},
        }};
       
        glDisable(GL_DEPTH_TEST); 
        screen_shader.bind();
        screen_shader.set_uniform("my_texture", render_target.color_texture(0));
        screen_mesh.draw();
    
        glEnable(GL_DEPTH_TEST); 

    }
}