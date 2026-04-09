/**
  ******************************************************************************
  * @file    css.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    23-January-2018
  * @brief   This file describes the sending of Cascade Style Sheet to a client
  *
  ******************************************************************************
  */

void sendCSS(WiFiClient client) {
  client.println(
    ":root {\n\
    --primary: #405070;\n\
    --background: #22374b;\n\
}\n\
html {\n\
    font-family: Verdana, Arial, sans-serif;\n\
    color: #ffffff;\n\
}\n\
body {\n\
    width: 75vw;\n\
    max-width: 1000px;\n\
    margin: auto;\n\
    background: var(--background);\n\
}\n\
* {\n\
    font: 14px/20px Tahoma;\n\
    box-sizing: border-box;\n\
}\n\
.input_elm {\n\
    width: 100%;\n\
    padding: 10px;\n\
    border: none;\n\
    appearance: none;\n\
    border-radius: 15px;\n\
    color: #ffffff;\n\
    background: var(--primary);\n\
}\n\
label {\n\
    display: block;\n\
}\n\
input:active,\n\
input:focus,\n\
select:active,\n\
select:focus {\n\
    outline: none;\n\
}\n\
#settings {\n\
    /* max-height: max(45vh, 400px); */\n\
    display: flex;\n\
    flex-wrap: wrap;\n\
    align-content: flex-start;\n\
    gap: 0 40px;\n\
}\n\
.section {\n\
    margin: 10px auto;\n\
}\n\
.menu_bar {\n\
    vertical-align: top;\n\
    padding: 15px;\n\
    width: 100%;\n\
}\n\
#logProgress {\n\
    height: 20px;\n\
    width: 100%;\n\
    margin: 0;\n\
    border-radius: 10px;\n\
    background: var(--primary);\n\
    transition: all ease 0.2s;\n\
}\n\
.menu_item {\n\
    margin: 15px 0;\n\
}\n\
@media (min-width: 500px) {\n\
    .menu_item, .menu_button{\n\
        max-width: 250px;\n\
    }\n\
    .subsection {\n\
        width: 250px !important;\n\
    }\n\
}\n\
.subsection {\n\
    width: 100%;\n\
}\n\
.menu_button {\n\
    width: 100%;\n\
    min-width: 200px;\n\
    margin: 10px 0;\n\
    padding: 10px;\n\
    border-radius: 15px;\n\
    text-align: center;\n\
    cursor: pointer;\n\
    display: block;\n\
    border: 1px solid #ffffff;\n\
    background: linear-gradient(to top right, #0d2dff, #5309ff 15%, #00000000 50%, #00000000) top right/400% 400%;\n\
    transition: all ease 0.2s;\n\
}\n\
.menu_button:hover {\n\
    /* font-weight: bold; */\n\
    letter-spacing: 1px;\n\
    background-position: bottom left;\n\
}\n\
.hidden_input {\n\
    opacity: 0;\n\
    width: 0;\n\
    height: 0;\n\
    overflow: hidden;\n\
    position: absolute;\n\
    z-index: -1;\n\
}\n\
.short_input_wrapper {\n\
    display: flex;\n\
    justify-content: space-between;\n\
    align-items: center;\n\
    gap: 20px;\n\
}\n\
.short_input_field {\n\
    width: 100%;\n\
}\n\
.input_field .heading {\n\
    display: block;\n\
    text-align: left;\n\
}\n\
.input_label {\n\
    /* width: 100%; */\n\
    margin: 10px 0 5px;\n\
    font-size: 16px;\n\
    text-align: left;\n\
}\n\
.inline_input {\n\
    display: flex;\n\
    align-items: center;\n\
    justify-content: space-between;\n\
}\n\
.colour_input {\n\
    width: 40px;\n\
    height: 40px;\n\
    padding: 0;\n\
    overflow: hidden;\n\
    &::-webkit-color-swatch-wrapper {\n\
        padding: 0;\n\
    }\n\
}\n\
.switch_input {\n\
    width: 80px;\n\
    height: 40px;\n\
    border-radius: 20px;\n\
    padding: 0;\n\
    display: flex;\n\
    cursor: pointer;\n\
    transition: all ease 0.2s;\n\
    .knob {\n\
        width: calc(100% - 20px);\n\
        min-width: 30px;\n\
        border-radius: 25px;\n\
        background: #00000050;\n\
        margin: 5px;\n\
        appearance: none;\n\
        cursor: pointer;\n\
        transition: all ease 0.2s;\n\
    }\n\
    .knob:checked {\n\
        background: #ffffff80;\n\
    }\n\
    &::before,\n\
    &::after {\n\
        width: 0px;\n\
        content: '';\n\
        transition: all ease 0.2s;\n\
    }\n\
    &:has(input:checked)::before,\n\
    &:not(:has(input:checked))::after {\n\
        width: 100%;\n\
        transition-delay: 100ms;\n\
    }\n\
}\n\
.dropbox {\n\
    min-height: 150px;\n\
    margin: 10px 0;\n\
    border: 2px dashed #FFF;\n\
    border-radius: 20px;\n\
    background: var(--primary);\n\
    box-shadow: inset 0 0 50px #00000050;\n\
    transition: all ease 0.2s;\n\
    display: flex;\n\
    justify-content: center;\n\
    flex-direction: column;\n\
    align-items: center;\n\
    position: relative;\n\
    overflow: hidden;\n\
    .heading {\n\
        width: auto;\n\
        margin: 0;\n\
        padding: 60px 0;\n\
        font-size: 20px;\n\
        color: #FFF;\n\
        text-align: center;\n\
        transition: all ease 0.2s;\n\
        cursor: pointer;\n\
    }\n\
    .heading[overlay] {\n\
        position: absolute;\n\
        top: 0;\n\
        left: 0;\n\
        width: 100%;\n\
        height: 100%;\n\
        opacity: 0;\n\
        background: #00000090;\n\
    }\n\
}\n\
.dropbox:hover {\n\
    background: --background80;\n\
    box-shadow: inset 0 0 100px #00000050;\n\
    .heading {\n\
        letter-spacing: 2px;\n\
        width: 100%;\n\
    }\n\
    .heading[overlay] {\n\
        opacity: 0.8;\n\
    }\n\
}\n\
#images {\n\
    display: flex;\n\
    width: 100%;\n\
    justify-content: space-between;\n\
    gap: 20px;\n\
}\n\
@media (max-width: 1000px) {\n\
    #images {\n\
        flex-wrap: wrap;\n\
    }\n\
}\n\
.img_box {\n\
    width: 100%;\n\
    padding: 10px;\n\
}\n\
.img_elm, .image_section {\n\
    width: 100%;\n\
}\n\
.title {\n\
    font: 28px/35px arial;\n\
    margin: 20px 0 15px;\n\
}\n\
.heading {\n\
    width: 100%;\n\
    font-size: 20px;\n\
    margin: 40px 0 10px;\n\
    text-align: left;\n\
}\n\n");
}
