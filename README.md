# Documentation
The command line can take 5 different arguments :
- `-s/--scene` : the name of the scene we want to open.
- `-h/--height` : the height of the image created.
- `-w/--width` : the width of the image created.
- `-o/--output` : the name of the image that will be created.
- `-d/--shadows` : enable the shadows (disabled by default)

Every argument can be **optional** and will be defaulted if not written by the user.
The format for the scene to be loaded is as follows :
-  object : material x y z xRotation yRotation zRotation scale
-  Material : name r g b r g b r g b shininess
