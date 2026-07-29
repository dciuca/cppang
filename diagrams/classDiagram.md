```mermaid
classDiagram
    class GameLoop {
        +Run()
        -unique_ptr~IGameState~ currentState
        -ChangeState(newState) void
    }

    class GameStateRequest {
        <<Enumeration>>
        None
        ChangeToPlaying
        ChangeToMenu
        ChangeToGameOver
        Quit
    }

    class ShapeType {
        <<Enumeration>>
        CIRCLE
        RECTANGLE
    }

    class IGameState {
        <<interface>>
        +HandleInput() void
        +Enter() void
        +Update() void
        +Clean() void
        +Draw() void
        +Exit() void
        +GetGameStateRequest() GameStateRequest
        #RequestStateChange(GameStateRequest: request)
        #GameStateRequest gameStateRequest
    }

    class MenuState {
        +HandleInput() void
        +Enter() void
        +Update() void
        +Draw() void
        +Exit() void
    }

    class PlayingState {
        -vector~unique_ptr~IEntity~~ m_entities
        -vector~Players~~ m_players
        -vector~Balls~~ m_balls
        -vector~Harpoon~~ m_harpoons
        +HandleInput() void
        +Enter() void
        +Update() void
        +Clean() void
        +Draw() void
        +Exit() void
    }

    class GameOverState {
        +HandleInput() void
        +Enter() void
        +Update() void
        +Draw() void
        +Exit() void
    }

    class IEntity {
        <<interface>>
        -bool isActive
        +Vector2 position
        +Vector2 velocity
        +float speed
        +SetActive(active: bool) void
        +SetColor(color: Color) void
        +SetTexture(texturePath: string) void
        +GetDimensions() Vector2
        +GetShapeType() ShapeType
        +Update() void
        +Draw() void
    }

    class Player {
        -float width
        -float height
        -Color color
        -Texture2D texture
        -bool useTexture
        +Player(x, y, width, height, color, texturePath)
        +SetActive(active: bool) void
        +SetColor(color: Color) void
        +SetTexture(texturePath: string) void
        +GetDimensions() Vector2
        +Update() void
        +Draw() void
    }

    class Ball {
        -float radius
        -float angle
        -Color color
        -Texture2D texture
        -bool useTexture
        +Ball(x, y, radius, speed, angle, color)
        +SetActive(active: bool) void
        +SetColor(color: Color) void
        +SetTexture(texturePath: string) void
        +GetDimensions() Vector2
        +Update() void
        +Draw() void
    }

    class Harpoon {
        -float width
        -float height
        -Color color
        -Texture2D texture
        -bool useTexture
        +Harpoon(x, y, width, height, color, texturePath)
        +SetActive(active: bool) void
        +SetColor(color: Color) void
        +SetTexture(texturePath: string) void
        +GetDimensions() Vector2
        +Update() void
        +Draw() void
    }

    class Physics {
        <<static>>
        -ApplyGravity(entity: IEntity&, gravity: float) void
        -BounceOnWalls(entity: IEntity&, width: float, height float, ShapeType shape) void
        -UpdatePosition(entity: IEntity&) void
        +UpdateCharacter(entity: IEntity&) void
        +UpdateBall(entity: IEntity&) void
        +CheckBallPlayerCollision(ball: IEntity&, player: IEntity&) bool
    }

    GameLoop --> IGameState : contains
    IGameState <|-- MenuState : implements
    IGameState <|-- PlayingState : implements
    IGameState <|-- GameOverState : implements
    IGameState --> GameStateRequest: uses
    Physics --> ShapeType: uses
    IEntity --> ShapeType: uses
    
    PlayingState --> IEntity : contains
    IEntity <|-- Player : implements
    IEntity <|-- Ball : implements
    IEntity <|-- Harpoon : implements
    
    PlayingState --> Physics : uses
    Physics --> IEntity : operates on
```