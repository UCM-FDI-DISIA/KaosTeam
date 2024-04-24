#pragma once
#include <SDL.h>
#include <vector>

/*Struct con los datos de input de un botón específico*/
struct InputButton {
    bool keyDOWN; //True en el momento que el botón es pulsado
    bool pressed; //True 
    bool keyUP;

    InputButton() : keyDOWN(false), pressed(false), keyUP(false) {};

    /*Esta conversión debería mantener el comportamiento anterior para las clases en las que
    ya se ha implementado InputManager
    */
    operator bool() {
        return keyDOWN;
    }
};

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
    enum btnEnum {
        BTN_ACTION1,
        BTN_ACTION2,
        BTN_ACTION4,
        BTN_UP,
        BTN_DOWN,
        BTN_LEFT,
        BTN_RIGHT,
        BTN_ESCAPE,
        BTN_SPACE,
        END //Para tener un valor con el que crear y utilizar el array
    };

    //InputButton buttons[];
       std::vector<InputButton> buttons;
    static InputManager* instance;

    //Constructor vacio privado para poder instanciar desde dentro
    InputManager();
    //Destructor
    ~InputManager() {};

    //Actualiza el estado de los eventos
    void UpdateStates(const SDL_Event& event);
    //Establece todos los estados a false
    void ClearStates();
    void UptiCheck(btnEnum btn);
    void DowntiCheck(btnEnum btn);
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
    InputButton getAction1();
    InputButton getAction2();
    //InputButton getShift();
    InputButton getAction4();
    InputButton getUp();
    InputButton getDown();
    InputButton getLeft();
    InputButton getRight();
    InputButton getSpace();
    InputButton getEscape();
};

inline InputManager& im() {
    return *InputManager::GetInstance();
}