import pygame
from time import sleep
from numpy import deg2rad, sin, cos
from random import randint
from pygame import gfxdraw # <-- For Antialias Components

pygame.init()
pygame.font.init()

width, height = 1280, 720
half_width, half_height = int(width/2), int(height/2)

pygame.display.set_caption('NPIC Water Qaulity Monitoring')
screen = pygame.display.set_mode((width, height))

font = pygame.font.SysFont('Arial', 30)

WHITE = (255, 255, 255)
LIGHT_BLUE = (0, 102, 255)
BLACK = (0, 0, 0)
GRAY = (100, 96, 91)
DARKGRAY = (86, 86, 86)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
CYAN = (0, 255, 255)
MAGENTA = (255, 0, 255)

def map(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

def showText(x, y, text, color):
    textToShow = font.render(text, False, color)
    screen.blit(textToShow, (x, y))

class OdometerComponent:
    def __init__(self):
        self.small_radius = 15
    
    def drawCircle(self, x, y, color):
        gfxdraw.aacircle(screen, x, y, self.small_radius, color)
        gfxdraw.filled_circle(screen, x, y, self.small_radius, color)
    
    def draw(self, x, y, r, value, color):
        for angle in range(0, value):
            xArc = x + int(r*cos(deg2rad(angle-90)))
            yArc = y + int(r*sin(deg2rad(angle-90)))
            self.drawCircle(xArc, yArc, color)
            

class MainMonitoringUI:
    def __init__(self):
        self.mouseX, self.mouseY = 0, 0
        
        self.DissolvedOxygenOdometer = OdometerComponent()
        self.TemperatureOdometer = OdometerComponent()
    
    def showMousePos(self):
        self.mouseX, self.mouseY = pygame.mouse.get_pos()
        print(self.mouseX, self.mouseY)
    
    def run(self):
        screen.fill(WHITE)
        
        value = randint(0, 5000)                       # <-- Simulate Changing Dissolve Oxygen
        self.DissolvedOxygenOdometer.draw(half_width, half_height, 100, map(value, 0, 5000, 0, 360), LIGHT_BLUE)
        
        value1 = randint(0, 150)                       # <-- Simulate Changing Temperature
        self.TemperatureOdometer.draw(190, 350, 70, map(value1, 0, 150, 0, 360), GREEN)
        
        
        sleep(0.5)
        showText(520, 530, 'Dissolved Oxygen', BLUE)
        showText(590, 565, str(value), RED)
        
        showText(10, 10, 'Testing Text', RED)
        
        self.showMousePos()
        
        # END Here
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
        
        pygame.display.update()
        

if __name__ == '__main__':
    MonitoringUI = MainMonitoringUI()
    
    while True:
        MonitoringUI.run()
