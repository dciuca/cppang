#include "IGameState.h"
#include "IEntity.h"
#include <memory>

class PlayingState : public IGameState
{
public:
	PlayingState();
	~PlayingState() override = default;

	void Enter() override;
	void Update() override;
	void Draw() override;
	void Exit() override;

private:
	std::unique_ptr<IEntity> player;
	std::unique_ptr<IEntity> ball;
};