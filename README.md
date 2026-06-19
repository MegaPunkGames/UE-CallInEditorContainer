# UE-CallInEditorContainer
Helper Struct to have CallInEditor buttons nested within subcategories in the Details panel.

Unreal doesn't allow having nested CallInEditor in subcategories, hiding the buttons or reordering them in the Details panel. This plugin adds those features by forwarding the buttons to a "Container".

To do so, you must first add a UPROPERTY of class `FCallInEditorContainer`. You will use this UPROPERTY to mange your buttons using categories or meta tags (DisplayAfter, EditConditionHides, etc.)
You then simply need to mark your UFUNCTIONs with the `CallInEditorContainer=[PROPERTYNAME]` meta tag to place them within the container.

Example:
<img width="2267" height="762" alt="Capture d’écran 2026-06-14 111438" src="https://github.com/user-attachments/assets/2bbdccee-fe86-4397-8d37-924c7695d5cc" />

# Installation instruction
## From Fab
- Open Fab in the Epic Game Launcher
- Find the plugin from the catalog
- Clikc the install plugin button
- Select the desired engine version and click Install
- Open your game project
- Go to the Plugins page and find CallInEditorContainer
- Enable the plugin

## From Source
- Get the source from this repository.
- Copy the Plugins/CallInEditorContainer folder into your own game project's Plugin folder.
- Generate project files
- Compile in Visual studio
- Open your game project
- Go to the Plugins page and find CallInEditorContainer
- Enable the plugin
