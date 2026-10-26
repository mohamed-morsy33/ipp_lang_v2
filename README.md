<a><img width="128" alt="ipp_icon_png" src="https://github.com/user-attachments/assets/126116a0-128b-4a94-985a-a3c15b0eb837"></a>

## note 

This is a continuation of the IPP Language project I started last November,
but this time I will be writing it from scratch in C++.

## how to add the custom icon to your editor

1. Open the `media/` directory in your file explorer, and choose the icon you want to use 
2. Locate the extensions directory, and this depends on your OS and VS Code version:

**Windows**: `C:\Users\<username>\.vscode\extensions\` or for *Insiders* `C:\Users\<username>\.vscode-insiders\extensions\`

**macOS**: `~/.vscode/extensions/` or for *Insiders* `~/.vscode-insiders/extensions/`

**Linux**: `~/.vscode/extensions/` or for *Insiders* `~/.vscode-insiders/extensions/`

3. Install the **Material Icon Theme** extension from the VS Code Marketplace

4. Inside that extensions directory, find the extensions containing "material-icon-theme" in the name, and then open it. Then find the `icons/` directory inside it, and drag and drop the icon you want to use into that directory.

### configure `settings.json`

Now instruct the editor to map the `.xyz` extension to your custom file entry. 

1. Open VS Code 
2. Open the Command Palette (`Ctrl + Shift + P` on Windows or Linux / `Cmd + Shift + P` on Mac).
3. Type **Preferences: Open User Settings (JSON)** and press `Enter`.
4. Paste the following configuration block inside the root curly braces `{}`:

```json
"workbench.iconTheme": "material-icon-theme",
"material-icon-theme.files.associations": {
    "*.xyz": "xyz-icon"
},
```
> Do *not* include the `.svg` extension in the settings string. The extension adds it automatically during configuration parsing. 


Now reload the window and you should see your icon in the explorer sidebar.
