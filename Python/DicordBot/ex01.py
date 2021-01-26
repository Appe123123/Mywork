import sys
sys.path.append('C:/Users/Hyun/Desktop/Study/Python/temp')
import discord
import traceback
from discord import channel
from discord.ext import commands, tasks
import youtube_dl
import re
from abcdef import token

que = {}
playerlist = {}
playlist = list() #재생목록 리스트
bot = commands.Bot(command_prefix='>>')

@bot.event #print ERROR MESSAGES
async def on_command_error(ctx, error):
    tb = traceback.format_exception(type(error), error, error.__traceback__)
    err = [line.rstrip() for line in tb]
    errstr = '\n'.join(err)
    if isinstance(error, commands.NotOwner):
        await ctx.send('봇 주인만 사용 가능한 명령어입니다')
    else:
        await ctx.send('존재하지 않는 명령어입니다.')
        print(err)
        
@bot.event
async def on_ready():
    await bot.change_presence(status=discord.Status.online)
    print('The bot {0.user} has successfully been turned online!'.format(bot))



@bot.command(
    help = "BOT joins to your voice channel. If you're not in voice channel, error will be occured"
) ##BOT join to the voice channel
async def join(ctx):
    channel = ctx.author.voice.channel
    await channel.connect()

@bot.command() ##BOT exit from voice channel
async def leave(ctx):
    await ctx.voice_client.disconnect()


@bot.command()
@commands.is_owner()
async def offline(ctx):
   
    await bot.change_presence(status=discord.Status.offline)
    await ctx.send('봇 상태를 오프라인으로 변경했습니다.')
    

@bot.command()
@commands.is_owner()
async def online(ctx):
    await bot.change_presence(status=discord.Status.online)
    await ctx.send('봇 상태를 온라인으로 변경했습니다.')

@bot.command()
async def hello(ctx):
    await ctx.send('안녕하세요')

@bot.command(
    help = "send ping and PONG!"
)
async def ping(ctx):
    await ctx.send(f'pong! {round(round(bot.latency, 4)*1000)}ms')


@bot.command() #kill BOT by command
@commands.is_owner()
async def shutdown(ctx):
    await bot.change_presence(status=discord.Status.offline)
    await ctx.bot.logout()
    print('\nsuccessfully turn off the BOT!')




bot.run(f'{token}')