# encoding=utf-8
import math

import pygame
import random

# 1.初始化界面
pygame.init()
# 定义窗口的宽和高
screen_width = 800
screen_height = 600

# 2.生成一个窗口()pygame.display.set_mode(元组)；返回surface对象
screen = pygame.display.set_mode((screen_width, screen_height))

# 加载音乐
pygame.mixer.music.load('bg.wav')
# 循环播放
pygame.mixer.music.play(-1)
# 加载撞击声
bao_sound=pygame.mixer.Sound('exp.wav')
# 加载图片
# 1.把图片加载到内存中
bgImg = pygame.image.load('bg.png')
# print(type(bgImg))

# 加载玩家图片到内存
player = pygame.image.load('player.png')
# 设置玩家的宽和高
player_width = 64
player_height = 64
# 设置玩家的x坐标和y坐标
playerX = (screen_width - player_width) // 2
playerY = screen_height - player_height
# 设置玩家的速度
playerStep = 0


# 定义方法，飞机移动
def move_player():
    # 当修改全局变量要是用关键字global
    global playerX, playerY, playerStep
    # 绘制玩家飞机
    screen.blit(player, (playerX, playerY))
    # 飞机向右移动，向左动
    playerX += playerStep
    # 限定飞机右移不出界，
    if playerX >= 800 - 64:
        playerX = 800 - 64
    if playerX <= 0:
        playerX = 0


# ------------定义敌人类-----------
class Enemy:
    # 初始化敌人属性
    def __init__(self):
        # 加载敌人的图片
        self.img = pygame.image.load("enemy.png")
        # 敌人的x坐标
        self.x = random.randint(200, 600)
        # 敌人的y坐标
        self.y = random.randint(50, 250)
        # 敌人移动的速度
        self.step = random.randint(2, 4)

    # 重置敌人
    def reset(self):
        # 敌人的x坐标
        self.x = random.randint(200, 600)
        # 敌人的y坐标
        self.y = random.randint(50, 250)


# 敌人的数量6
numbers = 6
# 保存所有敌人
enemies = []
for i in range(numbers):  # 0,1,2,3,4,5
    enemies.append(Enemy())


# 敌人移动方法
def move_enemy():
    # 如何绘制每个敌人
    for b in enemies:
        screen.blit(b.img, (b.x, b.y))
        # 敌人向右移
        b.x += b.step
        # b.y+=b.step
        # 限定界限
        if b.x >= 800 - 64 or b.x < 0:
            b.step *= -1
            # 敌人向下移
            b.y += 20


# -----------定义子弹----------
class Bullet:
    def __init__(self):
        # 加载子弹图片
        self.img = pygame.image.load('bullet.png')
        # 初始化子弹的x
        self.x = playerX + 16  # 64-32/2
        # 初始化子弹的y
        self.y = playerY
        # 初始子弹的速度
        self.step = 7

    # 撞击方法
    def hit(self):
        # 对敌人进行遍历，判断是否撞击
        for e in enemies:
            if (distance(self.x, self.y, e.x, e.y) < 30):
                bao_sound.play()
                # 敌人重置
                e.reset()


# 创建子弹列表'
bullets = []


# 子弹动
def move_bullet():
    # 遍历子弹列表
    for b in bullets:
        # 绘制子弹
        screen.blit(b.img, (b.x, b.y))
        # 判断撞击
        b.hit()

        # 子弹向上移动
        b.y -= b.step
        # 如果子弹出界，移除子弹
        if b.y < 0:
            bullets.remove(b)


# 求距离函数
def distance(bx, by, ex, ey):
    a = bx - ex
    b = by - ey
    return math.sqrt(a * a + b * b)


# 游戏的主循环
running = True
while running:
    # 把图片绘制到游戏窗口上
    # 窗口画谁？画的位置？
    screen.blit(bgImg, (0, 0))
    # 事件监听
    for event in pygame.event.get():
        # 判断事件类型
        if event.type == pygame.QUIT:
            running = False
            # 判断事件按下键盘
        if event.type == pygame.KEYDOWN:
            # 判断键的含义,如果是右移
            if event.key == pygame.K_RIGHT:
                playerStep = 3
                # 判断键的含义,如果是左移
            if event.key == pygame.K_LEFT:
                playerStep = -3
            # 判断按得是宫格键
            if event.key == pygame.K_SPACE:
                # 创建字弹
                print("发射子弹")
                bullets.append(Bullet())
        if event.type == pygame.KEYUP:
            playerStep = 0

    # 加载飞机
    move_player()
    # 敌人动
    move_enemy()
    # 子弹动
    move_bullet()

    # 更新界面:pygame.display.update();必须在循环的最后
    # 更新界面:pygame.display.update();必须在循环的最后
    pygame.display.update()
    