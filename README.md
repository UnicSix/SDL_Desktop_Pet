# Compile the pet
- In my use case, I have SDL3, SDL_ttf, SDL_image compiled and installed in my computer,  
if you want to create a new build dir and use cmake .. command directly, make sure you've done the same  
so find_package can run without errors.
- So far the program doesn't do anything with flecs yet, you can remove or exclude the files associated  
with flecs lib if you don't want to install unnecessary library in your computer.
- Once you run ```cmake .. ``` and ```cmake --build .``` successfully in build directory,
you can run ```./sdl_desktop_pet``` and it creates 1 window with piggy animation by default,
specify the quantity of piggy by add nunber after the command.  
Running ```./sdl_desktop_pet 5``` will create 5 piggys in total.
