// action.h (ou qualquer outro nome de arquivo adequado)
#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <windows.h>

struct Action {
    enum ActionType { Click, KeyPress };
    ActionType type;
    POINT cord;  // Para cliques
    int key;  // Para teclas

    Action(ActionType t, POINT cords, int keyPas) : type(t), cord(cords), key(keyPas) {}
};

#endif // ACTION_H
