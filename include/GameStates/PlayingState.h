#include "IGameState.h"
#include "IEntity.h"
#include "Physics.h"
#include "Player.h"
#include <memory>
#include <vector>

class PlayingState : public IGameState
{
public:
    PlayingState();
    ~PlayingState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;

private:
    std::vector<std::unique_ptr<IEntity>> m_entities;
    std::vector<Player *> m_players;
};