#include "IGameState.h"
#include "IEntity.h"
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

public:
	void AddBall(std::unique_ptr<IEntity> newBall);

private:
	std::unique_ptr<IEntity> player;
	std::vector<std::unique_ptr<IEntity>> balls;
};