#ifndef GRAPHICOBSERVER_H
#define GRAPHICOBSERVER_H

#include "observer.h"
#include "window.h"
#include "queue.h"
#include "player.h"
#include "canvas.h"
#include <vector> // Include vector for std::vector

class GraphicObserver : public Observer {
private:
    Player* player1;
    Player* player2;
    Xwindow window; // Xwindow instance for graphical rendering

    // Previous canvas states for both players
    std::vector<std::vector<char>> previousCanvas1;
    std::vector<std::vector<char>> previousCanvas2;

public:
    // Constructor
    GraphicObserver(Player* p1, Player* p2, int width, int height);

    void drawBorders();

    // Notify method to update the graphical display
    void notify() override;

    // Destructor
    ~GraphicObserver();
};

#endif // GRAPHICOBSERVER_H
