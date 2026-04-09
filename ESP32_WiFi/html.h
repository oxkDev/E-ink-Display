/**
  ******************************************************************************
  * @file    html.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    23-January-2018
  * @brief   This file describes the sending of HTML-page to a client
  *
  ******************************************************************************
  */

void sendHtml(WiFiClient client, IPAddress myIP) {
  client.print(
"<!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset='utf-8'>\n\
    <meta name='viewport' content='width=device-width, initial-scale=1'>\n\
    <title>E-Ink Image Uploader</title>\n\
    <link rel='icon' href='data:;base64,='>\n\
    <link rel='stylesheet' href='styles.css'>\n\
    <script src='scriptA.js'></script>\n\
    <script src='scriptB.js'></script>\n\
    <script src='scriptC.js'></script>\n\
    <script src='scriptD.js'></script>\n\
</head>\n\
<body>\n\
    <div id='epdSettings' class='section'>\n\
        <div class='title'>Device Settings</div>\n\
        <div class='menu_item input_field'>\n\
            <label for='ipAddress' class='input_label'>Device IP</label>\n\
            <input id='ipAddress' class='input_elm' type='text' value='192.168.88.150'>\n\
        </div>\n\
        <div id='displayOptions' class='menu_item input_field'>\n\
            <label for='display' class='input_label'>Display Type</label>\n\
            <select id='displayType' class='input_elm' name='display'></select>\n\
        </div>\n\
    </div>\n\
    <div id='settings' class='section'>\n\
        <div id='imgSettings' class='subsection'>\n\
            <div class='title'>Image Adjustments</div>\n\
            <div id='position' class='short_input_wrapper menu_item'>\n\
                <div class='short_input_field'>\n\
                    <label for='imgX' class='input_label'>X</label>\n\
                    <input id='imgX' class='input_elm' type='text' value='0'>\n\
                </div>\n\
                <div class='short_input_field'>\n\
                    <label for='imgY' class='input_label'>Y</label>\n\
                    <input id='imgY' class='input_elm' type='text' value='0'>\n\
                </div>\n\
            </div>\n\
            <div id='dimensions' class='short_input_wrapper menu_item'>\n\
                <div class='short_input_field'>\n\
                    <label for='imgW' class='input_label'>W</label>\n\
                    <input id='imgW' class='input_elm' type='text'>\n\
                </div>\n\
                <div class='short_input_field'>\n\
                    <label for='imgH' class='input_label'>H</label>\n\
                    <input id='imgH' class='input_elm' type='text'>\n\
                </div>\n\
            </div>\n\
            <div id='scaleOptions' class='menu_item input_field'>\n\
                <label for='scaleMode' class='input_label'>Scale Mode</label>\n\
                <select id='scaleMode' class='input_elm'>\n\
                    <option value='original'>Original</option>\n\
                    <option value='fit' selected>Fit</option>\n\
                    <option value='fill'>Fill</option>\n\
                </select>\n\
            </div>\n\
            <div id='rotateOptions' class='menu_item input_field'>\n\
                <label for='rotateMode' class='input_label'>Rotation</label>\n\
                <select id='rotateMode' class='input_elm'>\n\
                    <option value='0' selected>0°</option>\n\
                    <option value='90'>90°</option>\n\
                    <option value='180'>180°</option>\n\
                    <option value='270'>270°</option>\n\
                </select>\n\
            </div>\n\
        </div>\n\
        <div id='paletteSettings' class='subsection'>\n\
            <div class='title'>Process Settings</div>\n\
            <div id='bgOptions' class='menu_item input_field inline_input'>\n\
                <label for='bgColour' class='input_label'>Background Colour</label>\n\
                <input id='bgColour' class='colour_input input_elm' type='color' value='#FFFFFF' />\n\
            </div>\n\
            <label class='menu_item input_field inline_input'>\n\
                <div class='input_label'>Colour</div>\n\
                <div class='input_elm switch_input'>\n\
                    <input id='setColour' class='knob' type='checkbox' checked='true' />\n\
                </div>\n\
            </label>\n\
            <label class='menu_item input_field inline_input'>\n\
                <div class='input_label'>Dithering</div>\n\
                <div class='input_elm switch_input'>\n\
                    <input id='setDithering' class='knob' type='checkbox' checked='true' />\n\
                </div>\n\
            </label>\n\
        </div>\n\
    </div>\n\
    <div class='menu_button'>\n\
        <label for='upload'>Upload</label>\n\
        <input class='hidden_input' id='upload' type='button' />\n\
    </div>\n\
    <div class='section' id='logs'>\n\
        <div class='short_input_wrapper'>\n\
            <div id='wsStatus'>● Connecting to Hardware...</div>\n\
            <div id='logTag'>Ready</div>\n\
        </div>\n\
        <div class='section' id='logProgress'></div>\n\
    </div>\n\
    <div class='section' id='images'>\n\
        <div class='image_section'>\n\
            <div class='title'>Original</div>\n\
            <canvas id='source' class='hidden_input'></canvas>\n\
            <div class='dropbox' id='dropbox'>\n\
                <input id='dropboxInput' type='file' accept='image/*' class='hidden_input' />\n\
                <label class='heading' id='dropboxHeading' for='dropboxInput'>Click to add image.</label>\n\
                <div id='srcBox' class='img_box'></div>\n\
            </div>\n\
        </div>\n\
        <div id='dstBox' class='image_section'></div>\n\
    </div>\n\
</body>\n\
</html>");
}
