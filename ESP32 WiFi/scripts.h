/**
******************************************************************************
* @file    scripts.h
* @author  Waveshare Team
* @version V1.0.0
* @date    23-January-2018
* @brief   This file describes the sending of JavaScript codes to a client
*
******************************************************************************
*/

void sendJS_A(WiFiClient client) {
  client.println(
    "const epdData = [\n\
    { width: 200, height: 200, paletteIndex: 0, name: '1.54' },\n\
    { width: 200, height: 200, paletteIndex: 3, name: '1.54b' },\n\
    { width: 152, height: 152, paletteIndex: 5, name: '1.54c' },\n\
    { width: 122, height: 250, paletteIndex: 0, name: '2.13' },\n\
    { width: 104, height: 212, paletteIndex: 1, name: '2.13b' },\n\
    { width: 104, height: 212, paletteIndex: 5, name: '2.13c' },\n\
    { width: 104, height: 212, paletteIndex: 0, name: '2.13d' },\n\
    { width: 176, height: 264, paletteIndex: 0, name: '2.7' },\n\
    { width: 176, height: 264, paletteIndex: 1, name: '2.7b' },\n\
    { width: 128, height: 296, paletteIndex: 0, name: '2.9' },\n\
    { width: 128, height: 296, paletteIndex: 1, name: '2.9b' },\n\
    { width: 128, height: 296, paletteIndex: 5, name: '2.9c' },\n\
    { width: 128, height: 296, paletteIndex: 0, name: '2.9d' },\n\
    { width: 400, height: 300, paletteIndex: 0, name: '4.2' },\n\
    { width: 400, height: 300, paletteIndex: 1, name: '4.2b' },\n\
    { width: 400, height: 300, paletteIndex: 5, name: '4.2c' },\n\
    { width: 600, height: 448, paletteIndex: 0, name: '5.83' },\n\
    { width: 600, height: 448, paletteIndex: 1, name: '5.83b' },\n\
    { width: 600, height: 448, paletteIndex: 5, name: '5.83c' },\n\
    { width: 640, height: 384, paletteIndex: 0, name: '7.5' },\n\
    { width: 640, height: 384, paletteIndex: 1, name: '7.5b' },\n\
    { width: 640, height: 384, paletteIndex: 5, name: '7.5c' },\n\
    { width: 800, height: 480, paletteIndex: 0, name: '7.5 V2' },\n\
    { width: 800, height: 480, paletteIndex: 1, name: '7.5b V2' },\n\
    { width: 880, height: 528, paletteIndex: 1, name: '7.5b HD' },\n\
    { width: 600, height: 448, paletteIndex: 7, name: '5.65f' },\n\
    { width: 880, height: 528, paletteIndex: 0, name: '7.5 HD' },\n\
    { width: 280, height: 480, paletteIndex: 0, name: '3.7' },\n\
    { width: 152, height: 296, paletteIndex: 0, name: '2.66' },\n\
    { width: 648, height: 480, paletteIndex: 1, name: '5.83b V2' },\n\
    { width: 128, height: 296, paletteIndex: 1, name: '2.9b V3' },\n\
    { width: 200, height: 200, paletteIndex: 1, name: '1.54b V2' },\n\
    { width: 104, height: 214, paletteIndex: 1, name: '2.13b V3' },\n\
    { width: 128, height: 296, paletteIndex: 0, name: '2.9 V2' },\n\
    { width: 400, height: 300, paletteIndex: 1, name: '4.2b V2' },\n\
    { width: 152, height: 296, paletteIndex: 1, name: '2.66b' },\n\
    { width: 648, height: 480, paletteIndex: 0, name: '5.83 V2' },\n\
    { width: 640, height: 400, paletteIndex: 7, name: '4.01 f' },\n\
    { width: 176, height: 264, paletteIndex: 1, name: '2.7b V2' },\n\
    { width: 122, height: 250, paletteIndex: 0, name: '2.13 V3' },\n\
    { width: 122, height: 250, paletteIndex: 1, name: '2.13 B V4' },\n\
    { width: 240, height: 360, paletteIndex: 0, name: '3.52' },\n\
    { width: 176, height: 264, paletteIndex: 0, name: '2.7 V2' },\n\
    { width: 122, height: 250, paletteIndex: 0, name: '2.13 V4' },\n\
    { width: 400, height: 300, paletteIndex: 0, name: '4.2 V2' },\n\
    { width: 960, height: 680, paletteIndex: 0, name: '13.3k' },\n\
    { width: 800, height: 480, paletteIndex: 0, name: '4.26' },\n\
    { width: 128, height: 296, paletteIndex: 1, name: '2.9bV4' },\n\
    { width: 960, height: 680, paletteIndex: 1, name: '13.3b' },\n\
    { width: 800, height: 480, paletteIndex: 6, name: '7.3E' },\n\
    { width: 1200, height: 1600, paletteIndex: 6, name: '13.3E' }\n\
];\n\
const palettes = [\n\
    [[0, 0, 0], [255, 255, 255]],\n\
    [[0, 0, 0], [255, 255, 255], [127, 0, 0]],\n\
    [[0, 0, 0], [255, 255, 255], [127, 127, 127]],\n\
    [[0, 0, 0], [255, 255, 255], [127, 127, 127], [127, 0, 0]],\n\
    [[0, 0, 0], [255, 255, 255]],\n\
    [[0, 0, 0], [255, 255, 255], [220, 180, 0]],\n\
    [[20, 15, 50], [255, 255, 255], [255, 255, 0], [190, 80, 80], [80, 90, 220], [120, 240, 140]],\n\
    [[0, 0, 0], [255, 255, 255], [0, 255, 0], [0, 0, 255], [255, 0, 0], [255, 255, 0], [255, 128, 0]]\n\
];\n\
function setPalette(paletteIndex) {\n\
    curPaletteRGB = palettes[paletteIndex];\n\
    curPaletteLab = curPaletteRGB.map(c => rgbToLab(c[0], c[1], c[2]));\n\
    if (paletteIndex < 6) {\n\
        curPaletteCodes = [0, 1, 2, 3];\n\
        return;\n\
    }\n\
    curPaletteCodes = {\n\
        6: [0, 1, 2, 3, 5, 6],\n\
        7: [0, 1, 2, 3, 4, 5, 6]\n\
    }[paletteIndex];\n\
};\n\
function getElm(n) { return document.getElementById(n); }\n\
function setInn(n, i) { document.getElementById(n).innerHTML = i; }\n\
let srcImg = new Image(),\n\
    dstImgData,\n\
    epdIndex = 50,\n\
    curPaletteRGB = [],\n\
    curPaletteLab = [],\n\
    labCache = new Map(),\n\
    curPaletteCodes = [],\n\
    dstColourCodesBuffer = new Uint8Array();\n\
function processFiles(files) {\n\
    if (!files.length) return;\n\
    let file = files[0];\n\
    let reader = new FileReader();\n\
    srcImg = new Image();\n\
    reader.onload = function (e) {\n\
        setInn('srcBox', '<img id=\"imgView\" class=\"img_elm\">');\n\
        let img = getElm('imgView');\n\
        img.src = e.target.result;\n\
        srcImg.src = e.target.result;\n\
            console.log('new image: ' + srcImg.src);\n\
        const dropboxHeading = getElm('dropboxHeading');\n\
        dropboxHeading.setAttribute('overlay', 'true');\n\
        dropboxHeading.innerHTML = 'Click to replace image.';\n\
        setTimeout(() => processImg(), 100);\n\
    };\n\
    reader.readAsDataURL(file);\n\
}\n\
function onDrop(e) {\n\
    console.log('image dropped.');\n\
    e.stopPropagation();\n\
    e.preventDefault();\n\
    let files = e.dataTransfer.files;\n\
    processFiles(files);\n\
}\n\
function stopEvent(e) {\n\
    e.stopPropagation();\n\
    e.preventDefault();\n\
}\n\
function displayOptionElm(vl, tx) {\n\
    return '<option name=\"kind\" value=\"' + vl + '\" ' + (vl == 50 ? 'selected' : '') + '>' + tx + '</option>';\n\
}\n\
function rbClick(index) {\n\
    getElm('imgW').value = +epdData[index].width;\n\
    getElm('imgH').value = +epdData[index].height;\n\
    epdIndex = index;\n\
}\n\
window.onload = function () {\n\
    document.ondragover = () => {\n\
        let dropboxHeading = getElm('dropboxHeading');\n\
        dropboxHeading.setAttribute('dropping', 'true');\n\
        dropboxHeading.innerText = 'Drop image here.';\n\
    };\n\
    document.ondragend = () => {\n\
        let dropboxHeading = getElm('dropboxHeading');\n\
        dropboxHeading.setAttribute('dropping', 'false');\n\
        dropboxHeading.innerText = 'Click to ' + (srcImg ? 'replace' : 'add') + ' image.';\n\
    };\n\
    getElm('dropboxInput').onchange = (e) => processFiles(e.target.files);\n\
    let dropbox = getElm('dropbox');\n\
    document.ondragenter = stopEvent;\n\
    document.ondragover = stopEvent;\n\
    dropbox.ondrop = onDrop;\n\
    srcImg = null;\n\
    epdIndex = 0;\n\
    getElm('upload').onclick = () => {\n\
        uploadImage();\n\
    }\n\
    const inputIDs = ['setColour', 'setDithering', 'rotateMode', 'scaleMode', 'imgH', 'imgW', 'imgY', 'imgX'];\n\
    for (let i = 0; i < inputIDs.length; i++)\n\
        getElm(inputIDs[i]).onchange = processImg;\n\
        let optionsHTML = '';\n\
        for (let i = 0; i < epdData.length; i++)\n\
        optionsHTML += displayOptionElm(i, epdData[i].name);\n\
        setInn('displayType', optionsHTML);\n\
        const selectionElm = getElm('displayType');\n\
    selectionElm.onchange = (e) => {\n\
        rbClick(selectionElm.value);\n\
        processImg();\n\
    };\n\
    rbClick(selectionElm.value);\n\
}\n\n");
}

void sendJS_B(WiFiClient client) {
  client.println(
    "let source;\n\
let shiftX, shiftY, imgW, imgH, sW, sH;\n\
function setColourCode(pixelIndex, colourIndex) {\n\
    let dataIndex = pixelIndex * 4;\n\
    dstImgData.data[dataIndex] = curPaletteRGB[colourIndex][0];\n\
    dstImgData.data[dataIndex + 1] = curPaletteRGB[colourIndex][1];\n\
    dstImgData.data[dataIndex + 2] = curPaletteRGB[colourIndex][2];\n\
    dstImgData.data[dataIndex + 3] = 255;\n\
        dstColourCodesBuffer[pixelIndex] = curPaletteCodes[colourIndex];\n\
}\n\
function getWeightedErrRGB(originalRGB, errRGB, weight) {\n\
    return [\n\
        originalRGB[0] + (errRGB[0] * weight),\n\
        originalRGB[1] + (errRGB[1] * weight),\n\
        originalRGB[2] + (errRGB[2] * weight)\n\
    ];\n\
}\n\
function rgbToLab(r, g, b) {\n\
    r /= 255;\n\
    g /= 255;\n\
    b /= 255;\n\
        r = r > 0.04045 ? Math.pow((r + 0.055) / 1.055, 2.4) : r / 12.92;\n\
    g = g > 0.04045 ? Math.pow((g + 0.055) / 1.055, 2.4) : g / 12.92;\n\
    b = b > 0.04045 ? Math.pow((b + 0.055) / 1.055, 2.4) : b / 12.92;\n\
        let x = r * 0.4124 + g * 0.3576 + b * 0.1805;\n\
    let y = r * 0.2126 + g * 0.7152 + b * 0.0722;\n\
    let z = r * 0.0193 + g * 0.1192 + b * 0.9505;\n\
        x /= 0.95047;\n\
    z /= 1.08883;\n\
        let f = (t) => t > 0.008856 ? Math.pow(t, 1 / 3) : (7.787 * t) + (16 / 116);\n\
        let fx = f(x);\n\
    let fy = f(y);\n\
    let fz = f(z);\n\
        return [\n\
        (116 * fy) - 16,\n\
        500 * (fx - fy),\n\
        200 * (fy - fz)\n\
    ];\n\
}\n\
function getNear(r, g, b) {\n\
    r = Math.round(r * 1000) / 1000;\n\
    g = Math.round(g * 1000) / 1000;\n\
    b = Math.round(b * 1000) / 1000;\n\
        let key = (r << 16) | (g << 8) | b;\n\
        let lab = labCache.get(key);\n\
    if (!lab) {\n\
        lab = rgbToLab(r, g, b);\n\
        labCache.set(key, lab);\n\
    }\n\
        let best = 0;\n\
    let bestDist = Infinity;\n\
        for (let i = 0; i < curPaletteLab.length; i++) {\n\
        let p = curPaletteLab[i];\n\
                let dL = lab[0] - p[0];\n\
        let da = lab[1] - p[1];\n\
        let db = lab[2] - p[2];\n\
                let dist = dL * dL + da * da + db * db;\n\
                if (dist < bestDist) {\n\
            bestDist = dist;\n\
            best = i;\n\
        }\n\
    }\n\
        return best;\n\
}\n\
function hexToRgb(hex) {\n\
    return [\n\
        parseInt(hex.substring(1, 3), 16),\n\
        parseInt(hex.substring(3, 5), 16),\n\
        parseInt(hex.substring(5, 7), 16)\n\
    ];\n\
}\n\
function preprocessImage() {\n\
    let scaleMode = getElm('scaleMode').value;\n\
    let rotation = parseInt(getElm('rotateMode').value);\n\
    let targetW = parseInt(getElm('imgW').value);\n\
    let targetH = parseInt(getElm('imgH').value);\n\
    let srcW = srcImg.width;\n\
    let srcH = srcImg.height;\n\
    \n\
    let rotW = srcW;\n\
    let rotH = srcH;\n\
        if (rotation === 90 || rotation === 270) {\n\
        rotW = srcH;\n\
        rotH = srcW;\n\
    }\n\
        let scale = 1;\n\
        if (scaleMode === 'fit')\n\
        scale = Math.min(targetW / rotW, targetH / rotH);\n\
    else if (scaleMode === 'fill')\n\
        scale = Math.max(targetW / rotW, targetH / rotH);\n\
    else if (scaleMode === 'original')\n\
        scale = 1;\n\
            let drawW = srcW * scale;\n\
    let drawH = srcH * scale;\n\
        let canvas = document.createElement('canvas');\n\
    canvas.width = targetW;\n\
    canvas.height = targetH;\n\
        let ctx = canvas.getContext('2d');\n\
        let bgHex = getElm('bgColour').value;\n\
    ctx.fillStyle = bgHex;\n\
    ctx.fillRect(0, 0, canvas.width, canvas.height);\n\
        ctx.save();\n\
        ctx.translate(targetW / 2 + shiftX, targetH / 2 + shiftY);\n\
    ctx.rotate(rotation * Math.PI / 180);\n\
        ctx.drawImage(\n\
        srcImg,\n\
        -drawW / 2,\n\
        -drawH / 2,\n\
        drawW,\n\
        drawH\n\
    );\n\
        ctx.restore();\n\
        return ctx.getImageData(0, 0, canvas.width, canvas.height);\n\
}\n\n");
}

void sendJS_C(WiFiClient client) {
  client.println(
    "function processImg() {\n\
    dithering = getElm('setDithering').checked;\n\
    colour = getElm('setColour').checked;\n\
    if (!srcImg) {\n\
        alert('Please select an image first.');\n\
        return;\n\
    }\n\
    let paletteIndex = epdData[epdIndex].paletteIndex;\n\
    setPalette(paletteIndex);\n\
    if (colour) {\n\
        if (palettes[paletteIndex] === undefined || palettes[paletteIndex].length <= 2) {\n\
            alert('Selected display does not support colour.');\n\
            colour = false;\n\
            getElm('setColour').checked = false;\n\
        }\n\
    } else\n\
        if (palettes[paletteIndex] !== undefined && palettes[paletteIndex].length > 2)\n\
            setPalette(0);\n\
    shiftX = parseInt(getElm('imgX').value);\n\
    shiftY = parseInt(getElm('imgY').value);\n\
    imgW = parseInt(getElm('imgW').value);\n\
    imgH = parseInt(getElm('imgH').value);\n\
    let srcImgData = preprocessImage();\n\
    let sW = srcImgData.width;\n\
    let sH = srcImgData.height;\n\
    dstColourCodesBuffer = new Uint8Array(imgW * imgH);\n\
    if ((imgW < 3) || (imgH < 3)) {\n\
        alert('Image is too small');\n\
        return;\n\
    }\n\
    getElm('dstBox').innerHTML = '<div class=\"title\">Processed image</div><canvas id=\"processedImg\" class=\"img_elm\"></canvas>';\n\
    let canvasElm = getElm('processedImg');\n\
    canvasElm.width = imgW;\n\
    canvasElm.height = imgH;\n\
    dstImgData = new ImageData(imgW, imgH);\n\
    let bgRGB = hexToRgb(getElm('bgColour').value);\n\
    let pixelIndex = 0;\n\
    if (!dithering) {\n\
        let bgIndex = getNear(bgRGB[0], bgRGB[1], bgRGB[2]);\n\
        for (let row = 0; row < imgH; row++) {\n\
            if ((row < 0) || (row >= sH)) {\n\
                for (let x = 0; x < imgW; x++, pixelIndex++) setColourCode(pixelIndex, bgIndex);\n\
                continue;\n\
            }\n\
            for (let col = 0; col < imgW; col++) {\n\
                if ((col < 0) || (col >= sW)) {\n\
                    setColourCode(pixelIndex, bgIndex);\n\
                    pixelIndex++;\n\
                    continue;\n\
                }\n\
                let pos = (row * sW + col) * 4;\n\
                setColourCode(pixelIndex, getNear(srcImgData.data[pos], srcImgData.data[pos + 1], srcImgData.data[pos + 2]));\n\
                pixelIndex++;\n\
            }\n\
        }\n\
    } else {\n\
        let errRowA = 0;\n\
        let errRowB = 1;\n\
        let errBuffers = [Array.from({ length: imgW }, () => [0, 0, 0]), Array.from({ length: imgW }, () => [0, 0, 0])];\n\
            for (let row = 0; row < imgH; row++) {\n\
            [errRowA, errRowB] = [errRowB, errRowA];\n\
                    for (let col = 0; col < imgW; col++)\n\
                errBuffers[errRowB][col] = [0, 0, 0];\n\
                        for (let col = 0; col < imgW; col++) {\n\
                let srcRGB = [0, 0, 0];\n\
                if ((col < 0) || (col >= sW) || (row < 0) || (row >= sH)) {\n\
                    srcRGB = bgRGB;\n\
                } else {\n\
                    let pos = (row * sW + col) * 4;\n\
                    srcRGB = [\n\
                        srcImgData.data[pos],\n\
                        srcImgData.data[pos + 1],\n\
                        srcImgData.data[pos + 2]\n\
                    ]\n\
                }\n\
                let newRGB = [0, 0, 0];\n\
                for (let k = 0; k < 3; k++) {\n\
                    newRGB[k] = Math.max(0, Math.min(255, srcRGB[k] + errBuffers[errRowA][col][k]));\n\
                }\n\
                let colourIndex = getNear(newRGB[0], newRGB[1], newRGB[2]);\n\
                setColourCode(pixelIndex, colourIndex);\n\
                pixelIndex++;\n\
                let errRGB = [\n\
                    newRGB[0] - curPaletteRGB[colourIndex][0],\n\
                    newRGB[1] - curPaletteRGB[colourIndex][1],\n\
                    newRGB[2] - curPaletteRGB[colourIndex][2]\n\
                ];\n\
                if (errRGB[0] === 0 && errRGB[1] === 0 && errRGB[2] === 0) continue;\n\
                if (row == imgH - 1) continue;\n\
                            if (!col) {\n\
                    errBuffers[errRowA][col + 1] = getWeightedErrRGB(errBuffers[errRowA][col + 1], errRGB, 7 / 16);\n\
                    errBuffers[errRowB][col + 1] = getWeightedErrRGB(errBuffers[errRowB][col + 1], errRGB, 2 / 16);\n\
                    errBuffers[errRowB][col] = getWeightedErrRGB(errBuffers[errRowB][col], errRGB, 7 / 16);\n\
                } else if (col == imgW - 1) {\n\
                    errBuffers[errRowB][col] = getWeightedErrRGB(errBuffers[errRowB][col], errRGB, 9 / 16);\n\
                    errBuffers[errRowB][col - 1] = getWeightedErrRGB(errBuffers[errRowB][col - 1], errRGB, 7 / 16);\n\
                } else {\n\
                    errBuffers[errRowB][col - 1] = getWeightedErrRGB(errBuffers[errRowB][col - 1], errRGB, 3 / 16);\n\
                    errBuffers[errRowB][col] = getWeightedErrRGB(errBuffers[errRowB][col], errRGB, 5 / 16);\n\
                    errBuffers[errRowB][col + 1] = getWeightedErrRGB(errBuffers[errRowB][col + 1], errRGB, 1 / 16);\n\
                    errBuffers[errRowA][col + 1] = getWeightedErrRGB(errBuffers[errRowA][col + 1], errRGB, 7 / 16);\n\
                }\n\
            }\n\
        }\n\
    }\n\
    setTimeout(() => canvasElm.getContext('2d').putImageData(dstImgData, 0, 0), 100);\n\
}");
}

// void sendJS_D(WiFiClient client) {
//   client.print(
//     "let pxInd, stage, xhReq;\n\
// let rqPrf, rqMsg;\n\
// const maxChunkSize = ");
//   client.print(BUFF_MAX_CHUNK_SIZE);
//   client.println(";\n\
// function byteToStr(v) { return String.fromCharCode((v & 0xF) + 97, ((v >> 4) & 0xF) + 97); }\n\
// function wordToStr(v) { return byteToStr(v & 0xFF) + byteToStr((v >> 8) & 0xFF); }\n\
// function EPD_Send(cmd, next) {\n\
//     xhReq.open('POST', rqPrf + cmd, true);\n\
//     xhReq.send();\n\
//     if (next) stage++;\n\
//     return 0;\n\
// }\n\
// function EPD_Next() {\n\
//     lnInd = 0;\n\
//     pxInd = 0;\n\
//     EPD_Send('NEXT_', true);\n\
// }\n\
// function EPD_Done() {\n\
//     setInn('logTag', 'Complete!');\n\
//     return EPD_Send('SHOW_', true);\n\
// }\n\
// function EPD_Load(colourData, startProgress, endProgress) {\n\
//     let progress = (startProgress + (endProgress - startProgress) * pxInd / colourData.length);\n\
//     setInn('logTag', 'Sending to ' + epdData[epdIndex].name + ': ' + (Math.round(progress * 100) / 100).toFixed(2) + '% Complete');\n\
//     document.querySelector('#logProgress').style.width = progress + '%';\n\
//     return EPD_Send(rqMsg + wordToStr(rqMsg.length) + 'LOAD_', pxInd >= colourData.length);\n\
// }\n\
// function EPD_SendChunk(colourData, c, startProgress, endProgress) {\n\
//     rqMsg = '';\n\
//     if (c == -1) {\n\
//         while ((pxInd < colourData.length) && (rqMsg.length < maxChunkSize)) {\n\
//             let v = 0;\n\
//             for (let i = 0; i < 16; i += 2)\n\
//                 if (pxInd < colourData.length)\n\
//                     v |= (colourData[pxInd++] << i);\n\
//             rqMsg += wordToStr(v);\n\
//         }\n\
//     }\n\
//     else if (c == -2) {\n\
//         while ((pxInd < colourData.length) && (rqMsg.length < maxChunkSize)) {\n\
//             let v = 0;\n\
//             for (let i = 0; i < 16; i += 4)\n\
//                 if (pxInd < colourData.length)\n\
//                     v |= (colourData[pxInd++] << i);\n\
//             rqMsg += wordToStr(v);\n\
//         }\n\
//     }\n\
//     else {\n\
//         while ((pxInd < colourData.length) && (rqMsg.length < maxChunkSize)) {\n\
//             let v = 0;\n\
//             for (let i = 0; i < 8; i++)\n\
//                 if ((pxInd < colourData.length) && (colourData[pxInd++] != c))\n\
//                     v |= (128 >> i);\n\
//             rqMsg += byteToStr(v);\n\
//         }\n\
//     }\n\
//     return EPD_Load(colourData, startProgress, endProgress);\n\
// }\n\
// function EPD_Line(colourData, c, startProgress, endProgress) {\n\
//     let x;\n\
//     rqMsg = '';\n\
//     while (rqMsg.length < maxChunkSize) {\n\
//         x = 0;\n\
//         while (x < 122) {\n\
//             let v = 0;\n\
//             for (let i = 0; (i < 8) && (x < 122); i++, x++) if (colourData[pxInd++] != c) v |= (128 >> i);\n\
//             rqMsg += byteToStr(v);\n\
//         }\n\
//     }\n\
//     return EPD_Load(colourData, startProgress, endProgress);\n\
// }\n\
// function uploadImage() {\n\
//     let w = dstImgData.width;\n\
//     let h = dstImgData.height;\n\
//     if (!dstColourCodesBuffer) {\n\
//         alert('Please process the image before uploading.');\n\
//         return;\n\
//     }\n\
//     pxInd = 0;\n\
//     stage = 0;\n\
//     xhReq = new XMLHttpRequest();\n\
//     rqPrf = 'http://' + getElm('ipAddress').value + '/';\n\
//     if ([3, 39, 43].includes(epdIndex))\n\
//     {\n\
//         xhReq.onload = xhReq.onerror = function () {\n\
//             if (stage == 0) return EPD_Line(dstColourCodesBuffer, 0, 0, 100);\n\
//             if (stage == 1) return EPD_Done();\n\
//         };\n\
//         if (epdIndex > 25)\n\
//             return EPD_Send('EPD' + String.fromCharCode(epdIndex + -26 + 65) + '_', false);\n\
//         return EPD_Send('EPD' + String.fromCharCode(epdIndex + 97) + '_', false);\n\
//     }\n\
//     if (epdIndex == 40)\n\
//     {\n\
//         xhReq.onload = xhReq.onerror = function () {\n\
//             if (stage == 0) return EPD_Line(dstColourCodesBuffer, 0, 0, 50);\n\
//             if (stage == 1) return EPD_Next();\n\
//             if (stage == 2) return EPD_Line(dstColourCodesBuffer, 3, 50, 100);\n\
//             if (stage == 3) return EPD_Done();\n\
//         };\n\
//         if (epdIndex > 25)\n\
//             return EPD_Send('EPD' + String.fromCharCode(epdIndex + -26 + 65) + '_', false);\n\
//         return EPD_Send('EPD' + String.fromCharCode(epdIndex + 97) + '_', false);\n\
//     }\n\
//     if ([0, 3, 6, 7, 9, 12, 16, 19, 22, 26, 27, 28].includes(epdIndex)) {\n\
//         xhReq.onload = xhReq.onerror = function () {\n\
//             if (stage == 0) return EPD_SendChunk(dstColourCodesBuffer, 0, 0, 100);\n\
//             if (stage == 1) return EPD_Done();\n\
//         };\n\
//         if (epdIndex > 25)\n\
//             return EPD_Send('EPD' + String.fromCharCode(epdIndex + -26 + 65) + '_', false);\n\
//         return EPD_Send('EPD' + String.fromCharCode(epdIndex + 97) + '_', false);\n\
//     }\n\
//     if (epdIndex > 15 && epdIndex < 22) {\n\
//         xhReq.onload = xhReq.onerror = function () {\n\
//             if (stage == 0) return EPD_SendChunk(dstColourCodesBuffer, -1, 0, 100);\n\
//             if (stage == 1) return EPD_Done();\n\
//         };\n\
//         return EPD_Send('EPD' + String.fromCharCode(epdIndex + 97) + '_', false);\n\
//     }\n\
//     if ([25, 37].includes(epdIndex))\n\
//     {\n\
//         xhReq.onload = xhReq.onerror = function () {\n\
//             if (stage == 0) return EPD_SendChunk(dstColourCodesBuffer, -2, 0, 100);\n\
//             if (stage == 1) return EPD_Done();\n\
//         };\n\
//         if (epdIndex > 25)\n\
//             return EPD_Send('EPD' + String.fromCharCode(epdIndex + -26 + 65) + '_', false);\n\
//         return EPD_Send('EPD' + String.fromCharCode(epdIndex + 97) + '_', false);\n\
//     }\n\
//     if (epdIndex == 49)\n\
//     {\n\
//         xhReq.onload = xhReq.onerror = function () {\n\
//             if (stage == 0) return EPD_SendChunk(dstColourCodesBuffer, -2, 0, 100);\n\
//             if (stage == 1) return EPD_Done();\n\
//         };\n\
//         if (epdIndex > 25)\n\
//             return EPD_Send('EPD' + String.fromCharCode(epdIndex + -26 + 65) + '_', false);\n\
//         return EPD_Send('EPD' + String.fromCharCode(epdIndex + 97) + '_', false);\n\
//     }\n\
//     if (epdIndex == 50)\n\
//     {\n\
//         console.log('Loading 13.3 E 6 colours');\n\
//         let leftA = [];\n\
//         let rightA = [];\n\
//         for (let row = 0; row < h; row++) {\n\
//             let base = row * w;\n\
//             for (let xx = 0; xx < 600; xx++) leftA.push(dstColourCodesBuffer[base + xx]);\n\
//             for (let xx = 600; xx < w; xx++) rightA.push(dstColourCodesBuffer[base + xx]);\n\
//         }\n\
//         xhReq.onload = xhReq.onerror = function () {\n\
//             if (stage == 0) return EPD_SendChunk(leftA, -2, 0, 50);\n\
//             if (stage == 1) return EPD_Next();\n\
//             if (stage == 2) return EPD_SendChunk(rightA, -2, 50, 100);\n\
//             if (stage == 3) return EPD_Done();\n\
//         };\n\
//         if (epdIndex > 25)\n\
//             return EPD_Send('EPD' + String.fromCharCode(epdIndex - 26 + 65) + '_', false);\n\
//         return EPD_Send('EPD' + String.fromCharCode(epdIndex + 97) + '_', false);\n\
//     }\n\
//     else {\n\
//         console.log('Loading default EPD');\n\
//         xhReq.onload = xhReq.onerror = function () {\n\
//             console.log('*************');\n\
//             console.log(stage);\n\
//             console.log('*************');\n\
//             if (stage == 0 && epdIndex == 23) return EPD_SendChunk(dstColourCodesBuffer, 0, 0, 100);\n\
//             if (stage == 0) return EPD_SendChunk(dstColourCodesBuffer, ((epdIndex == 1) || (epdIndex == 12)) ? -1 : 0, 0, 50);\n\
//             if (stage == 1) return EPD_Next();\n\
//             if (stage == 2) return EPD_SendChunk(dstColourCodesBuffer, 3, 50, 100);\n\
//             if (stage == 3) return EPD_Done();\n\
//         };\n\
//         if (epdIndex > 25)\n\
//             return EPD_Send('EPD' + String.fromCharCode(epdIndex + -26 + 65) + '_', false);\n\
//         return EPD_Send('EPD' + String.fromCharCode(epdIndex + 97) + '_', false);\n\
//     }\n\
// }");
// }
void sendJS_D(WiFiClient client) {
  client.print(
    "let pxInd, stage;\n\
let rqMsg;\n\
const maxChunkSize = ");
  client.print(BUFF_MAX_CHUNK_SIZE);
  client.println(";\n\
let ws;\n\
let commandQueue = [];\n\
let isProcessing = false;\n\
\n\
function byteToStr(v) { return String.fromCharCode((v & 0xF) + 97, ((v >> 4) & 0xF) + 97); }\n\
function wordToStr(v) { return byteToStr(v & 0xFF) + byteToStr((v >> 8) & 0xFF); }\n\
\n\
window.addEventListener('load', () => {\n\
    let ip = getElm('ipAddress').value;\n\
    ws = new WebSocket('ws://' + ip + ':81/');\n\
    ws.onopen = () => { getElm('wsStatus').style.color = 'lime'; getElm('wsStatus').innerText = '● Hardware Connected'; };\n\
    ws.onclose = () => { getElm('wsStatus').style.color = 'red'; getElm('wsStatus').innerText = '● Disconnected'; };\n\
    ws.onmessage = (evt) => {\n\
        let msg = evt.data;\n\
        if (msg === 'ACK') { advanceQueue(); }\n\
        else if (msg === 'BUSY') { setInn('logTag', 'Hardware Processing (Busy Pin High)...'); }\n\
        else if (msg === 'DONE') { setInn('logTag', 'Upload Complete!'); document.querySelector('#logProgress').style.width = '100%'; }\n\
    };\n\
});\n\
\n\
function enqueueCommand(cmdData, logMsg, progress) {\n\
    commandQueue.push({ payload: cmdData, log: logMsg, prog: progress });\n\
}\n\
\n\
function advanceQueue() {\n\
    if (commandQueue.length === 0) { isProcessing = false; return; }\n\
    let nextCmd = commandQueue.shift();\n\
    setInn('logTag', nextCmd.log);\n\
    document.querySelector('#logProgress').style.width = nextCmd.prog + '%';\n\
    ws.send(nextCmd.payload);\n\
}\n\
\n\
function EPD_SendChunk(colourData, c, startProg, endProg) {\n\
    rqMsg = '';\n\
    let chunkStartProg = startProg;\n\
    let totalChunks = Math.ceil((colourData.length - pxInd) / (maxChunkSize/4));\n\
    let progStep = (endProg - startProg) / totalChunks;\n\
\n\
    while(pxInd < colourData.length) {\n\
        rqMsg = '';\n\
        if (c == -2) {\n\
            while ((pxInd < colourData.length) && (rqMsg.length < maxChunkSize)) {\n\
                let v = 0;\n\
                for (let i = 0; i < 16; i += 4)\n\
                    if (pxInd < colourData.length) v |= (colourData[pxInd++] << i);\n\
                rqMsg += wordToStr(v);\n\
            }\n\
        }\n\
        // (Include your original c == -1 and default logic here for other displays)\n\
        chunkStartProg += progStep;\n\
        enqueueCommand('LOAD_' + rqMsg, `Sending Chunk... ${(Math.round(chunkStartProg))}%`, chunkStartProg);\n\
    }\n\
}\n\
\n\
function uploadImage() {\n\
    if (!dstColourCodesBuffer) { alert('Process image first.'); return; }\n\
    if (ws.readyState !== WebSocket.OPEN) { alert('Hardware disconnected.'); return; }\n\
    \n\
    commandQueue = [];\n\
    pxInd = 0;\n\
    isProcessing = true;\n\
    \n\
    enqueueCommand('EPD_' + epdIndex, 'Initializing Display...', 5);\n\
    \n\
    if (epdIndex == 50) {\n\
        let leftA = [], rightA = [];\n\
        let w = dstImgData.width, h = dstImgData.height;\n\
        for (let row = 0; row < h; row++) {\n\
            let base = row * w;\n\
            for (let xx = 0; xx < 600; xx++) leftA.push(dstColourCodesBuffer[base + xx]);\n\
            for (let xx = 600; xx < w; xx++) rightA.push(dstColourCodesBuffer[base + xx]);\n\
        }\n\
        pxInd = 0; EPD_SendChunk(leftA, -2, 5, 50);\n\
        enqueueCommand('NEXT', 'Switching to Slave IC...', 50);\n\
        pxInd = 0; EPD_SendChunk(rightA, -2, 50, 95);\n\
        enqueueCommand('SHOW', 'Executing Direct Refresh...', 95);\n\
    }\n\
    // (Add fallback logic for other displays here if needed)\n\
    \n\
    advanceQueue();\n\
}\n");
}
