#pragma once
#include <SDL.h>
/*
* Encargado de capturar los eventos de entrada de controles del juego y enviarlas a las entidades pertinentes.
* 
* Para hacerla me he inspirado en los ejemplos de Samir.
* Diego Montenegro Calvo.
*/
class InputManager
{
private:
    //Definen los distintos botones que pueden estar pulsados o no
    enum state {
        BTN_ACTION1,
        BTN_ACTION2,
        BTN_SHIFT,
        BTN_ACTION4,
        BTN_UP,
        BTN_DOWN,
        BTN_LEFT,
        BTN_RIGHT,
        BTN_ESCAPE,
        BTN_SPACE,
        END //Para tener un valor con el que crear y utilizar el array
    };

    bool states[];
    static InputManager* instance;

    //Constructor vacio privado para poder instanciar desde dentro
    InputManager();
    //Destructor
    ~InputManager() {};

    //Actualiza el estado de los eventos
    void UpdateStates(const SDL_Event& event);
    //Establece todos los estados a false
    void ClearStates();
public:
    //Gestion para hacer singleton de InputManager
    InputManager(InputManager&) = delete;
    void operator=(const InputManager&) = delete;
    static InputManager* GetInstance() {
        if (instance == nullptr) {
            instance = new InputManager();
        }
        return instance;
    };

    void PollEvents();
    bool getAction1();
    bool getAction2();
    bool getShift();
    bool getAction4();
    bool getUp();
    bool getDown();
    bool getLeft();
    bool getRight();
    bool getSpace();
    bool getEscape();
};

inline InputManager& im() {
    return *InputManager::GetInstance();
}