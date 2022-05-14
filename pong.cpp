#include "raylib.h"

int main() {
    // Window width and height
    const int width = 640;
    const int height = 480;
    // Paddle width, height and movement speed
    const int paddleWidth = 8;
    const int paddleHeight = 64;
    const int paddleSpeed = 10;
    // Player 1 position and hitbox
    int player1X = 0;
    int player1Y = (height / 2) - (paddleHeight / 2);
    int lPlayer1X = player1X;
    int rPlayer1X = player1X + paddleWidth;
    int uPlayer1Y = player1Y;
    int dPlayer1Y = player1Y + paddleHeight;
    // Player 2 position and hitbox
    int player2X = width - paddleWidth;
    int player2Y = (height / 2) - (paddleHeight / 2);
    int lPlayer2X = player2X;
    int rPlayer2X = player2X + paddleWidth;
    int uPlayer2Y = player2Y;
    int dPlayer2Y = player2Y + paddleHeight;
    // Ball position, radius and hitbox
    int ballX = width / 2;
    int ballY = height / 2;
    const int ballRadius = 4;
    int lBallX = ballX - ballRadius;
    int rBallX = ballX + ballRadius;
    int uBallY = ballY - ballRadius;
    int dBallY = ballY + ballRadius;
    // Movement direction of the ball
    int ballDirX = 5;
    int ballDirY = 5;
    // Collision checking
    bool collisionPlayer1 = (dPlayer1Y >= uBallY) && (uPlayer1Y <= dBallY) && (rPlayer1X >= lBallX) && (lPlayer1X <= rBallX);
    bool collisionPlayer2 = (dPlayer2Y >= uBallY) && (uPlayer2Y <= dBallY) && (rPlayer2X >= lBallX) && (lPlayer2X <= rBallX);
    // Making the window and setting the FPS
    InitWindow(width, height, "Pong");
    SetTargetFPS(60);
    // Starts the game loop that can be broken out of only by pressing escape or closing the window
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        // Updating Player1 hitbox
        lPlayer1X = player1X;
        rPlayer1X = player1X + paddleWidth;
        uPlayer1Y = player1Y;
        dPlayer1Y = player1Y + paddleHeight;
        // Updating Player2 hitbox
        lPlayer2X = player2X;
        rPlayer2X = player2X + paddleWidth;
        uPlayer2Y = player2Y;
        dPlayer2Y = player2Y + paddleHeight;
        // Updating Ball hitbox
        lBallX = ballX - ballRadius;
        rBallX = ballX + ballRadius;
        uBallY = ballY - ballRadius;
        dBallY = ballY + ballRadius;
        // Updating collision checking
        collisionPlayer1 = (dPlayer1Y >= uBallY) && (uPlayer1Y <= dBallY) && (rPlayer1X >= lBallX) && (lPlayer1X <= rBallX);
        collisionPlayer2 = (dPlayer2Y >= uBallY) && (uPlayer2Y <= dBallY) && (rPlayer2X >= lBallX) && (lPlayer2X <= rBallX);
        // Drawing both Players, the ball and a dividing line onto the screen
        DrawRectangle(width/2, 0, 4, height, WHITE);
        DrawRectangle(player1X, player1Y, paddleWidth, paddleHeight, WHITE);
        DrawRectangle(player2X, player2Y, paddleWidth, paddleHeight, WHITE);
        DrawCircle(ballX, ballY, ballRadius, WHITE);
        // Making the ball bounce off the vertical edges of the screen
        if(ballY > height - ballRadius || ballY < ballRadius) ballDirY = -ballDirY;
        // Checking both player collisions and making the ball bounce off them in opposite direction if true
        if(collisionPlayer1) {
            ballDirX = -ballDirX;
            collisionPlayer1 = false;
        }
        if(collisionPlayer2) {
            ballDirX = -ballDirX;
            collisionPlayer2 = false;
        }
        // Making the ball move
        ballX += ballDirX;
        ballY += ballDirY;
        // Making the ball reset upon scoring
        if(ballX > width || ballX < 0) {
            ballX = width / 2;
            ballY = height / 2;
        }
        // Setting controls for both players
        if(IsKeyDown(KEY_W) && player1Y > 0) player1Y -= paddleSpeed;
        if(IsKeyDown(KEY_S) && player1Y < (height - paddleHeight)) player1Y += paddleSpeed;
        if(IsKeyDown(KEY_UP) && player2Y > 0) player2Y -= paddleSpeed;
        if(IsKeyDown(KEY_DOWN) && player2Y < (height - paddleHeight)) player2Y += paddleSpeed;

        EndDrawing();
    }
    CloseWindow();
}