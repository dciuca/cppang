#include "PlayingState.h"
#include "GameLevels.h"
#include "GameTypes.h"
#include "Physics.h"
#include "TextUtils.h"
#include "raylib.h"
#include <algorithm>

#include "Collectible.h"

PlayingState::PlayingState(LevelManager &levelManager)
    : m_levelManager(levelManager),
      m_waitingForReady(true),
      m_freezeTimer(4, false, false, nullptr)
{
    m_levelManager.GetLevelTimer().pause();

    LoadLevelBackground(m_levelManager.GetCurrentLevel());
    LoadLifebar();
    LoadPlayers();
    LoadObstacles(m_levelManager.GetCurrentLevel());
    LoadLevelBalls(m_levelManager.GetCurrentLevel());

    for (auto &entity : m_entities)
    {
        entity->SetActive(true);
    }
}

void PlayingState::HandleInput()
{
    if (m_waitingForReady)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            m_waitingForReady = false;
            m_levelManager.GetLevelTimer().activate();
        }
        return;
    }

    if (IsKeyPressed(KEY_P))
        PauseGame();

    if (m_players.size() > 0 && m_players[0]->IsActive())
    {
        Player *p1 = m_players[0];

        if (IsKeyDown(KEY_LEFT))
            p1->MoveLeft();
        else if (IsKeyDown(KEY_RIGHT))
            p1->MoveRight();
        else
            p1->StopMoving();

        if (IsKeyPressed(KEY_SPACE))
        {
            p1->StartShooting();
            LoadHarpoon(p1);
        }
    }
}

void PlayingState::Enter()
{
    gameStateRequest = GameStateRequest::None;
    m_font = LoadFont(GetFontPath());
}

void PlayingState::Update()
{
    if (m_waitingForReady)
        return;

    m_levelManager.GetLevelTimer().update();
    m_freezeTimer.update();

    UpdateEntities();

    HandleCollisions();

    if (!m_ballsToSplit.empty())
        SplitBalls(m_ballsToSplit);

    Cleanup();

    CheckWinCondition();
    CheckGameOver();
}

void PlayingState::Cleanup()
{
    auto removeInactive = [](auto &vec)
    {
        vec.erase(
            std::remove_if(vec.begin(), vec.end(),
                           [](auto *e)
                           { return !e->IsActive(); }),
            vec.end());
    };

    removeInactive(m_harpoons);
    removeInactive(m_balls);
    removeInactive(m_players);
    removeInactive(m_obstacles);
    removeInactive(m_collectibles);
}

void PlayingState::Draw() const
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawTexturePro(m_background,
                   {0, 0, (float)m_background.width, (float)m_background.height},
                   {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   {0, 0}, 0.0f, WHITE);

    DrawOffsetText(TextFormat("Scores: %d", m_levelManager.GetScore()), m_font, TextStyles::HUD(), 40.0f, 40.0f);
    
    DrawCenteredText(TextFormat("Time: %d",
                            m_waitingForReady
                                ? m_levelManager.GetLevelTimer().GetDuration()
                                : (int)m_levelManager.GetLevelTimer().GetTimeLeft()),
                 m_font,
                 TextStyles::HUD(),
                 (55.0f - (float)GetScreenHeight() / 2.0f));


    for (int i = 0; i < m_levelManager.GetLives(); i++)
    {
        DrawTexturePro(m_lifebar,
                       m_lifebarRect,
                       {(GetScreenWidth() - 50.0f) - (40.0f + i * 30.0f), 40.0f, 28.0f, 28.0f},
                       {0, 0}, 0.0f, WHITE);
    }

    for (const auto &entity : m_entities)
    {
        if (entity->IsActive())
            entity->Draw();
    }

    if (m_waitingForReady)
    {
        DrawCenteredText(TextFormat("LEVEL %d", m_levelManager.GetCurrentLevel()), m_font, TextStyles::Title(), 0.0f);
        DrawFadingText("Press SPACE to start", m_font, TextStyles::Subtitle(), 200.0f);
    }

    EndDrawing();
}

void PlayingState::Exit()
{
    UnloadTexture(m_background);
    UnloadTexture(m_lifebar);
    UnloadFont(m_font);
    m_entities.clear();
    m_balls.clear();
    m_harpoons.clear();
    m_obstacles.clear();
    m_players.clear();
}

// private methods
void PlayingState::UpdateEntities()
{
    for (auto &player : m_players)
    {
        Physics::UpdateCharacter(*player);
        player->Update();
    }

    for (auto &ball : m_balls)
        if (!m_freezeTimer.isActive())
            Physics::UpdateBall(*ball);

    for (auto &harpoon : m_harpoons)
        harpoon->Update();

    for (auto &obstacle : m_obstacles)
        if (!obstacle->IsFixed())
            Physics::UpdateObstacle(*obstacle);

    for (auto &collectible : m_collectibles)
        Physics::UpdateCollectible(*collectible);
}

void PlayingState::HandleCollisions()
{
    m_ballsToSplit.clear();
    HandleBallPlayerCollisions();
    HandleBallHarpoonCollisions();
    HandleBallObstacleCollisions();
    HandleHarpoonObstacleCollisions();
    HandlePlayerCollectibleCollisions();
}

void PlayingState::HandleBallPlayerCollisions()
{
    for (auto &ball : m_balls)
        for (auto &player : m_players)
            if (Physics::CheckAndResolveCircleRectCollision(*ball, *player) && !player->IsInvincible())
            {
                m_levelManager.SetLives(m_levelManager.GetLives() - 1);
                player->ActivateInvincibility();
            }
}

void PlayingState::HandleBallHarpoonCollisions()
{
    for (auto &ball : m_balls)
        for (auto &harpoon : m_harpoons)
        {
            if (!harpoon->IsActive())
                continue;
            if (Physics::CheckAndResolveCircleRectCollision(*ball, *harpoon))
            {
                harpoon->SetActive(false);
                m_ballsToSplit.push_back(ball);
                m_levelManager.SetScore(m_levelManager.GetScore() + 100);
            }
        }
}

void PlayingState::HandleBallObstacleCollisions()
{
    for (auto &ball : m_balls)
        for (auto &obstacle : m_obstacles)
            Physics::CheckAndResolveCircleRectCollision(*ball, *obstacle);
}

void PlayingState::HandleHarpoonObstacleCollisions()
{
    for (auto &harpoon : m_harpoons)
    {
        if (!harpoon->IsActive())
            continue;
        for (auto &obstacle : m_obstacles)
            if (Physics::CheckRectRectCollision(*harpoon, *obstacle))
                harpoon->SetActive(false);
    }
}

void PlayingState::HandlePlayerCollectibleCollisions()
{
    for (auto &collectible : m_collectibles)
        for (auto &player : m_players)
            if (Physics::CheckCircleRectCollision(*collectible, *player))
            {
                collectible->SetActive(false);

                switch(collectible->GetCollectibleType()) 
                {
                    case CollectibleType::Clock:
                    {
                        m_freezeTimer.activate();
                        break;
                    }
                    case CollectibleType::LifeUp:
                    {
                        if ( m_levelManager.GetLives() < m_levelManager.GetMaxLives() )
                            m_levelManager.SetLives(m_levelManager.GetLives() + 1);
                        break;
                    }

                    default:
                        break;
                }
            }
}

void PlayingState::SplitBalls(const std::vector<Ball *> &m_ballsToSplit)
{
    for (auto &ball : m_ballsToSplit)
    {
        ball->SetActive(false);

        // Check Collectible
        bool shouldDrop = ball->GetPendingCollectibleType() != CollectibleType::None &&
                  ball->GetGeneration() == ball->GetPendingDropGeneration();

        if (shouldDrop)
        {
            // collectible factory
            auto visual = GameLevels::GetCollectibleVisualConfig(ball->GetPendingCollectibleType());
            auto collectible = std::make_unique<Collectible>(
                ball->position.x, 
                ball->position.y, 
                ball->GetPendingCollectibleType(),
                visual.radius, 
                0.0f, 
                visual.color, 
                visual.texturePath
            );
            collectible->SetActive(true);
            m_collectibles.push_back(collectible.get());
            m_entities.push_back(std::move(collectible));
        }

        float newRadius = ball->GetDimensions().x / 2.0f;
        if (newRadius >= 10.0f)
        {
            auto ball1 = std::make_unique<Ball>(
                ball->position.x - newRadius,
                ball->position.y,
                newRadius,
                45.0f,
                ball->speed,
                ball->GetColor(),
                "",
                ball->GetGeneration() + 1,
                shouldDrop ? CollectibleType::None : ball->GetPendingCollectibleType(),
                shouldDrop ? 0 : ball->GetPendingDropGeneration()
            );
            auto ball2 = std::make_unique<Ball>(
                ball->position.x + newRadius,
                ball->position.y,
                newRadius,
                135.0f,
                ball->speed,
                ball->GetColor(),
                "",
                ball->GetGeneration() + 1,
                CollectibleType::None,
                0
            );

            ball1->SetTexture(ball->GetTexture());
            ball2->SetTexture(ball->GetTexture());

            ball1->SetActive(true);
            ball2->SetActive(true);
            m_balls.push_back(ball1.get());
            m_entities.push_back(std::move(ball1));

            m_balls.push_back(ball2.get());
            m_entities.push_back(std::move(ball2));
        }
    }
}

void PlayingState::PauseGame()
{
    m_waitingForReady = false;
    RequestStateChange(GameStateRequest::PauseGame);
}

// LOADERS

void PlayingState::LoadLevelBackground(unsigned short level)
{
    auto bgConfig = GameLevels::GetLevelBackground(m_levelManager.GetCurrentLevel());
    m_background = LoadTexture(bgConfig.texturePath.c_str());
}

void PlayingState::LoadLifebar()
{
    auto lifebarConfig = GameLevels::GetLifebarConfig();
    m_lifebar = LoadTexture(lifebarConfig.texturePath.c_str());
    m_lifebarRect = lifebarConfig.sourceRect;
}

void PlayingState::LoadPlayers()
{
    auto pConfig = GameLevels::GetPlayerConfig();
    auto p1 = std::make_unique<Player>(
        pConfig.x, pConfig.y, pConfig.width, pConfig.height, pConfig.color, pConfig.texturePath);
    m_players.push_back(p1.get());
    m_entities.push_back(std::move(p1));
}

void PlayingState::LoadLevelBalls(unsigned short level)
{
    m_balls.clear();
    auto balls = GameLevels::GetLevelBalls(level);
    for (const auto &config : balls)
    {
        auto ball = std::make_unique<Ball>(
            config.x, config.y, config.radius, config.angle, config.speed, config.color, config.texturePath,
            1, config.collectibleType, config.dropGeneration);

        m_balls.push_back(ball.get());
        m_entities.push_back(std::move(ball));
    }
}

void PlayingState::LoadObstacles(unsigned short level)
{
    auto obstacles = GameLevels::GetLevelObstacles(level);
    for (const auto &config : obstacles)
    {
        auto obstacle = std::make_unique<Obstacle>(
            config.x, config.y, config.width, config.height, config.isFixed, config.speed, config.color, config.texturePath);
        m_obstacles.push_back(obstacle.get());
        m_entities.push_back(std::move(obstacle));
    }
}

void PlayingState::LoadHarpoon(Player *p)
{
    auto hConfig = GameLevels::GetHarpoonConfig();
    auto harpoon = std::make_unique<Harpoon>(
        p->position.x + 12.0f,
        p->position.y + 10.0f,
        hConfig.width, hConfig.height, hConfig.speed, hConfig.color, hConfig.texturePath);
    harpoon->SetActive(true);
    m_harpoons.push_back(harpoon.get());
    m_entities.push_back(std::move(harpoon));
}

void PlayingState::CheckWinCondition()
{
    if (m_balls.size() == 0)
    {
        m_levelManager.SetScore(m_levelManager.GetScore() + ((unsigned int)m_levelManager.GetLevelTimer().GetTimeLeft() * 10));
        m_players[0]->Winning();
        RequestStateChange(GameStateRequest::ChangeToLevelComplete);
    }
}

void PlayingState::CheckGameOver()
{
    if (m_levelManager.GetLives() <= 0 || !m_levelManager.GetLevelTimer().isActive())
        RequestStateChange(GameStateRequest::ChangeToGameOver);
}
