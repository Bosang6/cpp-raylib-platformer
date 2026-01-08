#pragma onece
#include "ISceneUpdate.h"

class EndScene : public ISceneUpdate
{
public:
    EndScene(); // Costruttore di default
    EndScene(float finalScore); // Costruttore con punteggio
    void Update() override;

private:
    float score{0.0f};
};