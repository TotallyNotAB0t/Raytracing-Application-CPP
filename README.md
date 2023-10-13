# Documentation
The command line can take 6 different arguments :
- `-s/--scene` : A string, the name of the scene to be loaded.
- `-h/--height` : An int, the height of the image to create.
- `-w/--width` : An int, the width of the image to create.
- `-o/--output` : A string, the name of the image to create.
- `-d/--shadows` : A boolean, enable the shadows
- `-x/--checkboard` : A boolean, enable checkboard material

Every argument is **optional** and will be defaulted if not written by the user.
For more information, the help command can be run with `-e/--help`.

The format for the scene to be loaded is as follows :
- object : material x y z xRotation yRotation zRotation scale
- material : name r g b r g b r g b shininess
- light : x y z rDiffuse gDiffuse bDiffuse rSpecular gSpecular bSpecular

Scene example files can be found next to the executable.  
Some images output have been generated too.
