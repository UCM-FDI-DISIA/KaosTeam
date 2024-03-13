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
        BTN_ACTION3,
        BTN_UP,
        BTN_DOWN,
        BTN_LEFT,
        BTN_RIGHT,
        BTN_ESCAPE,
        BTN_SPACE,
        END //Para tener un valor con el que crear y utilizar el array
    };
    bool states[];
    //Constructor vac�o privado para poder instanciar desde dentro
    InputManager() { instance = nullptr; states[END] = {}; PollEvents(); };
    ~InputManager() {};
    static InputManager* instance;
    //Actualiza el estado de los eventos
    void UpdateStates(const SDL_Event& event);
    //Establece todos los estados a false
    void ClearStates();
public:
    InputManager(InputManager&) = delete;
    void operator=(const InputManager&) = delete;
    /*
    *Devuelve una instancia de InputManager, en caso de no haber una, la crea
    */
    static InputManager* GetInstance() {
        if (instance == nullptr) {
            instance = new InputManager();
        }
        return instance;
    };
    void PollEvents();
    bool getAction1();
    bool getAction2();
    bool getAction3();
    bool getUp();
    bool getDown();
    bool getLeft();
    bool getRight();
    bool getSpace();
};

inline InputManager& im() {
    return *InputManager::GetInstance();
}