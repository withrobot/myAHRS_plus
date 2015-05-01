#!/usr/bin/env python
# -*- coding: ms949 -*-
#
#  pygame example  
#   2015.05.01 ('c')void 
#     
#  ref. 
#   - http://www.codesampler.com/python.htm
#     - Deriving a custom sprite from Pygame 's Sprite class
#   - https://www.youtube.com/watch?v=h4jgpsB8EbQ
#   - http://www.iconarchive.com/show/flat-emoticons-icons-by-icons-land.html
#
#

import pygame
import numpy as np
import sys, traceback
from myahrs_plus import MyAhrsPlus

def loadImageFile( fileName, useColorKey = False ):
    try:
        image = pygame.image.load( fileName )
    except pygame.error:
        traceback.print_exc()
        raise IOError #from "File " + fileName + " not found."

    # To speed things up, convert the images to SDL's internal format.
    image = image.convert()

    if useColorKey is True:
        # Use the color of the pixel located at (0,0) as our color-key
        colorkey = image.get_at( (0,0) )
        image.set_colorkey( colorkey, pygame.RLEACCEL )

    # Return the image
    return image
    

class MovingTarget(pygame.sprite.Sprite):
    def __init__(self, image_path):
        
        # Intialize Sprite, our base class
        pygame.sprite.Sprite.__init__( self )

        self.image = loadImageFile(image_path, True)
        self.rect = self.image.get_rect()
        self.rect.topleft = (0, 150)

        surface = pygame.display.get_surface()
        self.area = surface.get_rect()

        self.x_velocity = 5.0 + 10*np.random.random()
        self.y_velocity = 1.0 + 10*np.random.random()

    def update( self ):

        # Simulate gravity by constantly adding some amount to the
        # sprite's Y velocity. This will pull the sprite down
        self.y_velocity += (0.5 + 0.1*np.random.random())

        # Now, move the sprite...
        self.rect.move_ip( (self.x_velocity, self.y_velocity ) )

        if self.rect.left < self.area.left or self.rect.right > self.area.right:
            # If the sprite is about to leave the screen's area, invert its 
            # X velocity so it will change its direction of travel
            self.x_velocity = -(self.x_velocity)
            self.rect.move_ip( (self.x_velocity, self.y_velocity ) )

            # Since we just bounced off the screen's left or right side,
            # flip the image so it seems to be going the other way.
            self.image = pygame.transform.flip( self.image, True, False )

        if self.rect.bottom > self.area.bottom:
            # If the sprite hits the bottom of the screen's area, invert its  
            # Y velocity so it will bounce back up
            self.y_velocity = -(self.y_velocity)
            self.rect.move_ip( (self.x_velocity, self.y_velocity ) )


class SniperTarget(object):
    def __init__(self, screen, ahrs):
        super(SniperTarget, self).__init__()
        self.mouse = pygame.image.load("images/sniper_target_3.png").convert_alpha()
        self.screen = screen
        self.ahrs = ahrs 
        
        surface = pygame.display.get_surface()
        self.area = surface.get_rect()
        width = self.area.right - self.area.left
        height = self.area.bottom - self.area.top
        self.center = (self.area.left + width/2, self.area.top + height/2)
        
        self.distance = height
                

    def update(self):
        if(self.ahrs is None):
            self.update_with_mouse()
        else:
            self.update_with_ahrs() 


    def update_with_mouse(self):
        mousex, mousey = pygame.mouse.get_pos()
        mousex -= self.mouse.get_width()/2
        mousey -= self.mouse.get_height()/2
        self.screen.blit(self.mouse, (mousex,mousey))    
        
        
    def update_with_ahrs(self):
        roll, pitch, yaw = self.ahrs.read_euler();
        
        delta_x = self.distance*np.sin(yaw*np.pi/180.0)
        delta_y = self.distance*np.sin(-pitch*np.pi/180.0)
        
        mousex, mousey = (int(self.center[0] + delta_x), int(self.center[1] + delta_y)) 
        self.screen.blit(self.mouse, (mousex,mousey))            


def main(serial_device):

    # initialize AHRS 
    if(serial_device is not None):
        ahrs = MyAhrsPlus(serial_device=serial_device)
        
        yaw_list = []
        for i in range(10):
            e = ahrs.read_euler();
            yaw_list.append(e[2])
        
        yaw_offset = np.mean(yaw_list)
        print "Yaw offset %.2f"%(yaw_offset)
        ahrs.set_yaw_offset(yaw_offset)            
    else:
        ahrs = None

    # Initialize pygame and create a window or screen to render to
    pygame.init()
    screen = pygame.display.set_mode( (640, 480) )

    # Create a background for our screen
    background = pygame.Surface( screen.get_size() )
    background = background.convert()
    background.fill( (255, 255, 255) )
    
    # create cross 
    pygame.mouse.set_visible(False)
    cross = SniperTarget(screen, ahrs)
    
    # create targets 
    all_target = pygame.sprite.Group()
    for image_path in ["images/target_%d.png"%i for i in range(12)]:
        all_target.add(MovingTarget(image_path))

    clock = pygame.time.Clock()

    while 1:
        clock.tick(30)

        # Handle input events
        pygame.event.pump()
        keyinput = pygame.key.get_pressed()
        if keyinput[pygame.K_ESCAPE] or pygame.event.peek(pygame.QUIT):
            break

        # Update targets
        all_target.update()

        # Display the background
        screen.blit( background, (0, 0) )
        all_target.draw( screen )

        # Draw cross 
        cross.update() 

        # Display the sprite
        pygame.display.flip()


if __name__ == '__main__': 
    
    if(len(sys.argv) < 2):
        serial_device = None
    else : 
        serial_device = sys.argv[1]
            
    main(serial_device)

