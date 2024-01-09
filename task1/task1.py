import pygame
import random

pygame.init()

WIDTH, HEIGHT = 800, 600
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Bouncing Ball")
FPS = 60

class BouncingBall:
    def __init__(self, radius=20, speed=5):
        self.radius = radius
        self.speed = speed
        self.position = [WIDTH // 2, HEIGHT // 2]
        self.direction = [random.choice([-1, 1]), random.choice([-1, 1])]

    def move(self):
        self.position[0] += self.speed * self.direction[0]
        self.position[1] += self.speed * self.direction[1]
        self.check_boundary_collision()

    def check_boundary_collision(self):
        if self.position[0] - self.radius <= 0 or self.position[0] + self.radius >= WIDTH:
            self.direction[0] *= -1  # Reverse the x-direction
        if self.position[1] - self.radius <= 0 or self.position[1] + self.radius >= HEIGHT:
            self.direction[1] *= -1  # Reverse the y-direction

    def draw(self):
        pygame.draw.circle(WIN, (0, 255, 0), (int(self.position[0]), int(self.position[1])), self.radius)

def main():
    run = True
    clock = pygame.time.Clock()
    ball = BouncingBall()

    while run:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False

        ball.move()

        # Draw background
        WIN.fill((255, 255, 255))

        # Draw ball
        ball.draw()

        # Update display
        pygame.display.flip()

    pygame.quit()

if __name__ == '__main__':
    main()
