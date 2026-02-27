#include "raylib.h"

class Paddle {

    public: 
        Rectangle rect;
        float speed;
        KeyboardKey upkey, downkey;

        Paddle(float x, float y, KeyboardKey up, KeyboardKey down) {
            rect = {x, y, 20, 100};
            speed = 500.0f;
            upkey = up;
            downkey = down;
        }

        void Update(float dt) {
            if (IsKeyDown(upkey) && rect.y > 0) rect.y -= speed*dt;
            if (IsKeyDown(downkey) && rect.y < GetScreenHeight() - rect.height) rect.y += speed*dt; 
        }

        void Draw() {
            DrawRectangleRec(rect, WHITE);
        }

};

class Ball {

    public:
        Vector2 position;
        Vector2 speed;
        float radius;

        Ball() {
            Reset();
            radius = 10;
        }

        void Reset() {
            position = { (float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
            speed = { 400, 400};
        }

        void Update(float dt) {

            position.x += speed.x*dt;
            position.y += speed.y*dt;

            if (position.y < 0 || position.y > GetScreenHeight()) speed.y += -1;
        }
        void Draw() {
            DrawCircleV(position, radius, YELLOW);
        }
};

class PongGame {

    public:

        Paddle  leftplayer;
        Paddle RightPlayer;
        Ball ball;
        int scoreleft = 0;
        int scoreright = 0;

        PongGame() :

            leftplayer(50, 200, KEY_W, KEY_S),
            RightPlayer(730, 200, KEY_UP, KEY_DOWN) {}

        void Update() {

            float dt = GetFrameTime();
            leftplayer.Update(dt);
            RightPlayer.Update(dt);
            ball.Update(dt);

            if ( CheckCollisionCircleRec(ball.position, ball.radius, leftplayer.rect) || CheckCollisionCircleRec(ball.position, ball.radius, RightPlayer.rect) ) ball.speed.x *= -1.1f;

            if (ball.position.x < 0) {
                scoreright++;
                ball.Reset();
            }

            if (ball.position.x > GetScreenHeight()) {
                scoreleft++;
                ball.Reset();
            }

        }

        void Draw() {

            leftplayer.Draw();
            RightPlayer.Draw();
            ball.Draw();
            DrawText(TextFormat("%i | %i", scoreleft, scoreright), 350, 20, 40, GRAY);
        
        }


};


        int main() {

            InitWindow( 800, 450, "PONG");
            SetTargetFPS(60);

            PongGame game;

                while ( !WindowShouldClose()) {

                    game.Update();
                    
                    BeginDrawing();

                        ClearBackground(BLACK);

                        game.Draw();

                    EndDrawing();
                }
                CloseWindow();

        return 0;
        }