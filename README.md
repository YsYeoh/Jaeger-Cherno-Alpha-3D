# Cherno Alpha Jaeger 3D Model in OpenGL (C++)

This project is a 3D model of the Cherno Alpha Jaeger, built using OpenGL and C++. The application allows you to control the Jaeger’s movements, camera views, lighting, and weapons in real-time. This project demonstrates basic 3D modeling, camera manipulation, and input handling using OpenGL.

## Features

- **Camera Control**: Move the camera up/down, left/right, zoom in/out, and rotate the camera.
- **Jaeger Movement**: Move and rotate the Jaeger using various key presses.
- **Leg and Arm Control**: Control individual limbs of the Jaeger, including leg and arm movements.
- **Weapon Control**: Enable and switch between melee and ranged weapons, as well as trigger ultimate moves.
- **Lighting**: Control the light source position to simulate different effects and lighting scenarios.
- **Pilot Room**: Open/close the Jaeger's pilot room.

## Samples

![alt text](demo/image-1.png?raw=true)
![alt text](demo/image-2.png?raw=true)
![alt text](demo/image-3.png?raw=true)
![alt text](demo/image-control-room.png?raw=true)
![alt text](demo/image-walk.png?raw=true)
![alt text](demo/image-weapon-1.png?raw=true)
![alt text](demo/image-weapon-2.png?raw=true)

## Controls

### Camera Controls

- **Up**: Move camera up
- **Down**: Move camera down
- **Left**: Move camera to the left
- **Right**: Move camera to the right
- **Q**: Zoom camera in
- **E**: Zoom camera out
- **Shift**: Change viewport
- **<**: Rotate camera clockwise
- **>**: Rotate camera counterclockwise

### Jaeger Movement

- **1**: Walk (Step by step)
- **W**: Rotate Jaeger to back / Walk
- **A**: Rotate Jaeger to left / Walk
- **S**: Rotate Jaeger to front / Walk
- **D**: Rotate Jaeger to right / Walk

### Leg and Arm Controls

- **U**: Move left leg
- **I**: Move left lower leg
- **O**: Move right leg
- **P**: Move right lower leg
- **J**: Rotate right arm
- **K**: Move right lower arm
- **L**: Move right arm
- **F**: Rotate left arm
- **G**: Move left lower arm
- **H**: Move left arm
- **0**: Open Jaeger pilot room

### Weapon Controls

- **C**: Enable/Disable Melee Weapon / Switch Weapon
- **V**: Enable/Disable Ranged Weapon / Switch Weapon
- **B**: Fire bullets
- **2**: Ultimate 1: Shoryuken
- **3**: Ultimate 2: Hurricane Kick

### Light Controls

- **Space**: Turn on/off light
- **4**: Move light position to left
- **5**: Move light position to right
- **6**: Move light position up
- **7**: Move light position down
- **8**: Move light position far
- **9**: Move light position near

### Reset

- **Enter**: Reset everything to default

## Getting Started

To get started with this project, you need the following:

- A C++ development environment (e.g., Visual Studio, GCC)
- OpenGL and GLUT libraries installed on your system
- The GLFW and GLM libraries (optional but recommended for improved camera control)

### Installation

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/yourusername/cherno-alpha-jaeger.git
    ```

2. Navigate to the project directory:

    ```bash
    cd cherno-alpha-jaeger
    ```

3. Make sure you have OpenGL, GLUT, and any required dependencies installed. If not, you can install them using your package manager (e.g., `apt`, `brew`, or `vcpkg`).

4. Compile the code:

    ```bash
    g++ -o JaegerModel main.cpp -lGL -lGLU -lglut -lGLEW
    ```

5. Run the program:

    ```bash
    ./JaegerModel
    ```

### Dependencies

- OpenGL
- GLUT (or FreeGLUT)
- GLM (for 3D math)
- GLEW (optional, for OpenGL extensions)

## Contributing

Feel free to fork the repository and submit issues or pull requests. Please ensure that any contributions follow the project's coding style and include tests where appropriate.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to OpenGL for providing the graphical framework.
- Special mention to [GLM](https://github.com/g-truc/glm) for providing the math library for handling 3D transformations.
- Thanks to [GLUT](https://www.opengl.org/resources/libraries/glut/) for the windowing and input handling framework.

