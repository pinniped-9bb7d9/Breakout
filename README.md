# Breakout

W Kavanagh \& N Merchant. Summer 2024

## controls

Move the mouse right to left to move the paddle right and left.
P to pause.

Enter to reply.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* \[DONE] Fix the compiler issues in the code

## Suggested tasks

* \[DONE] Implement mouse input for paddle
* \[DONE] Make paddle sensitivity adjustable with mouse wheel
* \[DONE] GameLoop
* Better UI (progress bar rather than timer for countdown)
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Leaderboards
* Sounds with increasing tone between bounces
* Better ball physics (Box2D)
* More ball types (e.g., multiball, sticky ball \[where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist

(00:10) Forked the original repository and run the project - received a compiler error originated from the 'PowerFireBall' class due to its header file being included in the header file for the 'PowerupBase' class. Removing this include resolved the compiler issue

(01:00) Implemented mouse input for paddle

(1:45) Adjustable mouse sensitivity using the mouse wheel

(3:30) Implemented render texture and ported CRT shader from ShaderToy

(3:50) Adjusted UI and game scene to fit within CRT shader vignette

(4:10) Implemented game loop

(5:00) Implemented screen shake when player loses a life

(5:20) Implemented new basic powerup (Flash Ball)

