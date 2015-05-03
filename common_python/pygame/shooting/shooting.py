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
    #image = image.convert()

    if useColorKey is True:
        # Use the color of the pixel located at (0,0) as our color-key
        colorkey = image.get_at( (0,0) )
        image.set_colorkey( colorkey, pygame.RLEACCEL )

    # Return the image
    return image


def load_explosion_image(fileName):
    #
    # 10 x 4 
    #
    BPP = 4 # RGBA 
    SOURCE_WIDTH = 930
    SOURCE_HEIGHT = 400
    
    SEGMENT_WITH = 93
    SEGMENT_HEIGHT = 100
    
    def read_subimage(image_str, x, y, width, height):
        sub_image_str = ""
        for y_sub in range(height):
            start_offset = (x + (y+y_sub)*SOURCE_WIDTH)*BPP
            end_offset = start_offset + width*BPP
            sub_image_str += image_str[start_offset:end_offset]
            
        return sub_image_str
    
    image = loadImageFile(fileName)
    image_str = pygame.image.tostring(image, "RGBA", True)
        
    sub_image_list = []
    for row in range(4):
        for col in range(10):
            sub_image_str = read_subimage(image_str, col*SEGMENT_WITH, 300 - row*SEGMENT_HEIGHT, SEGMENT_WITH, SEGMENT_HEIGHT)
            sub_image = pygame.image.fromstring(sub_image_str, (SEGMENT_WITH, SEGMENT_HEIGHT), "RGBA", True)        
            sub_image_list.append(sub_image)    
    
    return sub_image_list
    

class MovingTarget(pygame.sprite.Sprite):
    def __init__(self, id, image_path, explosion_images):
        
        # Intialize Sprite, our base class
        pygame.sprite.Sprite.__init__( self )
        
        self.id = id 
        
        self.state_killed = False 
        
        self.explosion_images = explosion_images
        self.explosion_image_index = 0
        
        self.image = loadImageFile(image_path, True)
            
        self.rect = self.image.get_rect()
        self.rect.topleft = (0, 150)

        surface = pygame.display.get_surface()
        self.area = surface.get_rect()

        self.x_velocity = 5.0 + 10*np.random.random()
        self.y_velocity = 1.0 + 10*np.random.random()

    def update( self ):
        
        if(self.state_killed == True):
            try:
                self.image = self.explosion_images[self.explosion_image_index]
                self.explosion_image_index += 1
            except:
                #traceback.print_exc()
                pass 
            
            self.rect.move_ip((0, 0))
            return 

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
            
    
    def kill(self, sniper_target_pos):
        if(self.state_killed == True):
            return False
        
        x, y, w, h = self.rect
        st_pos_x, st_pos_y = sniper_target_pos
        self.state_killed = ((x < st_pos_x and st_pos_x < x + w) and (y < st_pos_y and st_pos_y < y + h))
        
        if(self.state_killed):
            cx = x + w/2
            cy = y + h/2
            _, _, w, h = self.explosion_images[0].get_rect()
            self.rect = pygame.Rect(cx-w/2, cy-h/2, w, h)
            print "Target %d has been killed"%(self.id)
            return True
        else:
            return False  
        


class SniperTarget(object):
    def __init__(self, screen, ahrs):
        super(SniperTarget, self).__init__()
        self.sniper_target = pygame.image.load("images/sniper_target_3.png").convert_alpha()
        self.screen = screen
        self.ahrs = ahrs 
        
        surface = pygame.display.get_surface()
        self.area = surface.get_rect()
        width = self.area.right - self.area.left
        height = self.area.bottom - self.area.top
        self.center = (self.area.left + width/2, self.area.top + height/2)
        
        self.distance = height
        
        self.pos = (0, 0)
        

    def update(self):
        if(self.ahrs is None):
            self.update_with_mouse()
        else:
            self.update_with_ahrs() 
    
    
    def update_with_mouse(self):
        pos_x, pos_y = pygame.mouse.get_pos()
        
        self.pos = (pos_x, pos_y)
        
        pos_x -= self.sniper_target.get_width()/2
        pos_y -= self.sniper_target.get_height()/2
        self.screen.blit(self.sniper_target, (pos_x,pos_y))  
            
            
    def update_with_ahrs(self):
        roll, pitch, yaw = self.ahrs.read_euler();
        
        delta_x = self.distance*np.sin(yaw*np.pi/180.0)
        delta_y = self.distance*np.sin(-pitch*np.pi/180.0)
        
        pos_x, pos_y = (int(self.center[0] + delta_x), int(self.center[1] + delta_y)) 
        
        self.pos = (pos_x, pos_y)
        
        pos_x -= self.sniper_target.get_width()/2
        pos_y -= self.sniper_target.get_height()/2        
        self.screen.blit(self.sniper_target, (pos_x,pos_y))            


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
    sniper_target = SniperTarget(screen, ahrs)
    
    #
    explosion_images = load_explosion_image("images/explosion.png")
    
    # create targets 
    all_target_sprite_group = pygame.sprite.Group()
    all_target = []
    
    TARGET_NUM = 12
    
    for id, image_path in zip(range(TARGET_NUM), ["images/target_%d.png"%i for i in range(TARGET_NUM)]):
        target = MovingTarget(id, image_path, explosion_images)
        all_target_sprite_group.add(target)
        all_target.append(target)

    clock = pygame.time.Clock()

    while 1:
        clock.tick(30)

        # Handle input events
        pygame.event.pump()
        keyinput = pygame.key.get_pressed()
        if keyinput[pygame.K_ESCAPE] or pygame.event.peek(pygame.QUIT):
            break
        
        if keyinput[pygame.K_SPACE]:
            print "fire !", sniper_target.pos
            for target in all_target:
                if(target.kill(sniper_target.pos) == True):
                    break

        # Update targets
        all_target_sprite_group.update()

        # Display the background
        screen.blit( background, (0, 0) )
        all_target_sprite_group.draw( screen )

        # Draw sniper_target 
        sniper_target.update() 

        # Display the sprite
        pygame.display.flip()


if __name__ == '__main__': 
    
    if(len(sys.argv) < 2):
        serial_device = None
    else : 
        serial_device = sys.argv[1]
            
    main(serial_device)

