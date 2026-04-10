// SCRIPT A
const epdData = [
    { width: 200, height: 200, paletteIndex: 0, name: "1.54" },
    { width: 200, height: 200, paletteIndex: 3, name: "1.54b" },
    { width: 152, height: 152, paletteIndex: 5, name: "1.54c" },
    { width: 122, height: 250, paletteIndex: 0, name: "2.13" },
    { width: 104, height: 212, paletteIndex: 1, name: "2.13b" },
    { width: 104, height: 212, paletteIndex: 5, name: "2.13c" },
    { width: 104, height: 212, paletteIndex: 0, name: "2.13d" },
    { width: 176, height: 264, paletteIndex: 0, name: "2.7" },
    { width: 176, height: 264, paletteIndex: 1, name: "2.7b" },
    { width: 128, height: 296, paletteIndex: 0, name: "2.9" },
    { width: 128, height: 296, paletteIndex: 1, name: "2.9b" },
    { width: 128, height: 296, paletteIndex: 5, name: "2.9c" },
    { width: 128, height: 296, paletteIndex: 0, name: "2.9d" },
    { width: 400, height: 300, paletteIndex: 0, name: "4.2" },
    { width: 400, height: 300, paletteIndex: 1, name: "4.2b" },
    { width: 400, height: 300, paletteIndex: 5, name: "4.2c" },
    { width: 600, height: 448, paletteIndex: 0, name: "5.83" },
    { width: 600, height: 448, paletteIndex: 1, name: "5.83b" },
    { width: 600, height: 448, paletteIndex: 5, name: "5.83c" },
    { width: 640, height: 384, paletteIndex: 0, name: "7.5" },
    { width: 640, height: 384, paletteIndex: 1, name: "7.5b" },
    { width: 640, height: 384, paletteIndex: 5, name: "7.5c" },
    { width: 800, height: 480, paletteIndex: 0, name: "7.5 V2" },
    { width: 800, height: 480, paletteIndex: 1, name: "7.5b V2" },
    { width: 880, height: 528, paletteIndex: 1, name: "7.5b HD" },
    { width: 600, height: 448, paletteIndex: 7, name: "5.65f" },
    { width: 880, height: 528, paletteIndex: 0, name: "7.5 HD" },
    { width: 280, height: 480, paletteIndex: 0, name: "3.7" },
    { width: 152, height: 296, paletteIndex: 0, name: "2.66" },
    { width: 648, height: 480, paletteIndex: 1, name: "5.83b V2" },
    { width: 128, height: 296, paletteIndex: 1, name: "2.9b V3" },
    { width: 200, height: 200, paletteIndex: 1, name: "1.54b V2" },
    { width: 104, height: 214, paletteIndex: 1, name: "2.13b V3" },
    { width: 128, height: 296, paletteIndex: 0, name: "2.9 V2" },
    { width: 400, height: 300, paletteIndex: 1, name: "4.2b V2" },
    { width: 152, height: 296, paletteIndex: 1, name: "2.66b" },
    { width: 648, height: 480, paletteIndex: 0, name: "5.83 V2" },
    { width: 640, height: 400, paletteIndex: 7, name: "4.01 f" },
    { width: 176, height: 264, paletteIndex: 1, name: "2.7b V2" },
    { width: 122, height: 250, paletteIndex: 0, name: "2.13 V3" },
    { width: 122, height: 250, paletteIndex: 1, name: "2.13 B V4" },
    { width: 240, height: 360, paletteIndex: 0, name: "3.52" },
    { width: 176, height: 264, paletteIndex: 0, name: "2.7 V2" },
    { width: 122, height: 250, paletteIndex: 0, name: "2.13 V4" },
    { width: 400, height: 300, paletteIndex: 0, name: "4.2 V2" },
    { width: 960, height: 680, paletteIndex: 0, name: "13.3k" },
    { width: 800, height: 480, paletteIndex: 0, name: "4.26" },
    { width: 128, height: 296, paletteIndex: 1, name: "2.9bV4" },
    { width: 960, height: 680, paletteIndex: 1, name: "13.3b" },
    { width: 800, height: 480, paletteIndex: 6, name: "7.3E" },
    { width: 1200, height: 1600, paletteIndex: 6, name: "13.3E" }
];

const palettes = [
    [[0, 0, 0], [255, 255, 255]],
    [[0, 0, 0], [255, 255, 255], [127, 0, 0]],
    [[0, 0, 0], [255, 255, 255], [127, 127, 127]],
    [[0, 0, 0], [255, 255, 255], [127, 127, 127], [127, 0, 0]],
    [[0, 0, 0], [255, 255, 255]],
    [[0, 0, 0], [255, 255, 255], [220, 180, 0]],
    [[20, 15, 50], [255, 255, 255], [255, 255, 0], [185, 65, 50], [90, 90, 195], [60, 140, 70]], // B W Y R B G
    [[0, 0, 0], [255, 255, 255], [0, 255, 0], [0, 0, 255], [255, 0, 0], [255, 255, 0], [255, 128, 0]] // B W G B R Y O
]; //5.65f 7-colour E-Paper;

function setPalette(paletteIndex) {
    curPaletteRGB = palettes[paletteIndex];
    curPaletteLab = curPaletteRGB.map(c => rgbToLab(c[0], c[1], c[2]));

    if (paletteIndex < 6) {
        curPaletteCodes = [0, 1, 2, 3];
        return;
    }

    curPaletteCodes = {
        6: [0, 1, 2, 3, 5, 6],
        7: [0, 1, 2, 3, 4, 5, 6]
    }[paletteIndex];
};

function getElm(n) { return document.getElementById(n); }
function setInn(n, i) { document.getElementById(n).innerHTML = i; }

let srcImg = new Image(),
    dstImgData,
    epdIndex = 50,
    curPaletteRGB = [],
    curPaletteLab = [],
    rgbDistCache = new Map(),
    curPaletteCodes = [],
    dstColourCodesBuffer = new Uint8Array();


function processFiles(files) {
    if (!files.length) return;

    let file = files[0];
    let reader = new FileReader();
    srcImg = new Image();
    reader.onload = function (e) {
        getElm("srcBox").classList.remove("hidden");
        let img = getElm("imgView");
        img.src = e.target.result;
        srcImg.src = e.target.result;

        console.log("new image: " + srcImg.src);
        const dropboxHeading = getElm("dropboxHeading");
        dropboxHeading.setAttribute("overlay", "true");
        dropboxHeading.innerHTML = "Click to replace image.";

        setTimeout(() => processInputs(), 100);
    };

    reader.readAsDataURL(file);
}

function onDrop(e) {
    console.log("image dropped.");
    e.stopPropagation();
    e.preventDefault();
    let files = e.dataTransfer.files;
    processFiles(files);
}

function stopEvent(e) {
    e.stopPropagation();
    e.preventDefault();
}

function displayOptionElm(vl, tx) {
    return "<option name=\"kind\" value=\"" + vl + "\" " + (vl == 50 ? "selected" : "") + ">" + tx + "</option>";
}

function updateDimensions(index) {
    getElm("imgW").value = epdData[index].width;
    getElm("imgH").value = epdData[index].height;
    epdIndex = index;
}

function processInputs() {
    dithering = getElm("setDithering").checked;
    colour = getElm("setColour").checked;

    let paletteIndex = epdData[epdIndex].paletteIndex;

    setPalette(paletteIndex);

    if (colour) {
        if (palettes[paletteIndex] === undefined || palettes[paletteIndex].length <= 2) {
            alert("Selected display does not support colour.");
            colour = false;
            getElm("setColour").checked = false;
        }
    } else
        if (palettes[paletteIndex] !== undefined && palettes[paletteIndex].length > 2)
            setPalette(0);

    rgbDistCache = new Map();

    processImg();
}

// Elements Initialisation
window.addEventListener("load", () => {
    document.addEventListener("dragover", () => {
        let dropboxHeading = getElm("dropboxHeading");
        dropboxHeading.setAttribute("dropping", "true");
        dropboxHeading.innerText = "Drop image here.";
    });

    document.addEventListener("dragend", () => {
        let dropboxHeading = getElm("dropboxHeading");
        dropboxHeading.setAttribute("dropping", "false");
        dropboxHeading.innerText = `Click to  ${(srcImg ? "replace" : "add")} image.`;
    });

    getElm("dropboxInput").addEventListener("change", (e) => processFiles(e.target.files));

    let dropbox = getElm("dropbox");
    document.addEventListener("dragenter", stopEvent);
    document.addEventListener("dragover", stopEvent);
    dropbox.addEventListener("drop", onDrop);
    srcImg = null;
    epdIndex = 0;

    getElm("upload").addEventListener("click", uploadImage);
    getElm("clear").addEventListener("click", clearImage);

    const inputIDs = ["bgColour", "setColour", "setDithering", "rotateMode", "scaleMode", "imgH", "imgW", "imgY", "imgX"];

    for (let i = 0; i < inputIDs.length; i++)
        getElm(inputIDs[i]).addEventListener("change", processInputs);

    let optionsHTML = "";

    for (let i = 0; i < epdData.length; i++)
        optionsHTML += displayOptionElm(i, epdData[i].name);

    setInn("displayType", optionsHTML);

    const selectionElm = getElm("displayType");
    selectionElm.addEventListener("change", (e) => {
        updateDimensions(selectionElm.value);
        processInputs();
    });

    updateDimensions(selectionElm.value);

    getElm("ipAddress").addEventListener("change", () => {
        if (ws.readyState != WebSocket.OPEN)
            wsConnect();
    });

    getElm("ipAddress").addEventListener("focusout", () => {
        if (ws.readyState != WebSocket.OPEN)
            wsConnect();
    });
});

window.addEventListener("load", wsConnect);

let wsTimeout = 0, reqTimeout = 0;
let clientId = 0;

function wsConnect() {
    console.log("Hardware connecting.");
    clearTimeout(wsTimeout);
    let ip = getElm("ipAddress").value;
    ws = new WebSocket("ws://" + ip + "/ws");
    getElm("wsStatus").style.color = "";
    getElm("wsStatus").innerText = "● Connecting...";

    let wasConnected = false;
    ws.onopen = () => {
        wasConnected = true;
        getElm("wsStatus").style.color = "var(--success)";
        getElm("wsStatus").innerText = "● Hardware Connected";
        clearTimeout(wsTimeout);
        console.log("Hardware connected.");
        if (commandQueue.length != 0 && commandQueue[queueIndex].payload.startsWith("LOAD")) {
            console.log("Attempting Reconnection.");
            ws.send(`RECON_${clientId}`);
        }
    };

    ws.onclose = () => {
        getElm("wsStatus").style.color = "var(--error)";
        getElm("wsStatus").innerText = "● Disconnected";
        clearTimeout(reqTimeout);
        reqTimeout = 0;
        // commandQueue = [];
        console.log("Hardware disconnected.");
        wsTimeout = setTimeout(wsConnect, wasConnected ? 100 : 5000);
        wasConnected = false;
    };

    ws.onmessage = (evt) => {
        const msg = evt.data;
        clearTimeout(reqTimeout);
        reqTimeout = 0;

        if (msg == "READY") {
            setInn("logTag", "Hardware ready.");
            return;
        }
        if (msg.startsWith("ACK_")) {
            const newQueueIndex = parseInt(msg.substring(4));
            if (isNaN(newQueueIndex) || newQueueIndex != queueIndex) {
                console.error(`Unexpected queue index. Expected: ${queueIndex}, Received: ${newQueueIndex}`);
                queueIndex = newQueueIndex;
            }
            advanceQueue(++queueIndex);
            return;
        }
        if (msg == "BUSY") {
            setInn("logTag", "Hardware busy.");
            return;
        }
        if (msg == "BOOT") {
            setInn("logTag", "Hardware starting.");
            return;
        }
        if (msg == "DONE") {
            setInn("logTag", "Upload Successful!");
            document.querySelector("#logProgress").style.width = "100%";
            return;
        }
        if (msg.startsWith("RUNNING_")) {
            clientId = msg.substring(8);
            getElm("logTag").innerText += "...";
            console.log(`Running (session ${clientId})`);
            return;
        }
        if (msg.startsWith("RECON_")) {
            clientId = parseInt(msg.substring(6));
            setInn("logTag", `Reconnected to session ${clientId}`);
        }
        if (msg == "ERROR_UKNOWN_REQUEST") {
            if (isProcessing) {
                setInn("logTag", `Module missed data, retrying.`);
                advanceQueue();
            } else
                setInn("logTag", `Module Unknown Request: ${msg}`);
            return;
        }
        if (msg.startsWith("ERROR_")) {
            setInn("logTag", `Module Error: ${msg.replace("ERROR_", "").replaceAll("_", " ").toLowerCase()}`);
            console.log(`Error: ${msg}`);
            commandQueue = [];
            isProcessing = false;
        } else
            setInn("logTag", `Unknown Message: ${msg}`);
    };
}

// SCRIPT B
let imgW, imgH;

function setColourCode(pixelIndex, colourIndex) {
    let dataIndex = pixelIndex * 4;
    dstImgData.data[dataIndex] = curPaletteRGB[colourIndex][0];
    dstImgData.data[dataIndex + 1] = curPaletteRGB[colourIndex][1];
    dstImgData.data[dataIndex + 2] = curPaletteRGB[colourIndex][2];
    dstImgData.data[dataIndex + 3] = 255;

    dstColourCodesBuffer[pixelIndex] = curPaletteCodes[colourIndex];
}

function getWeightedErrRGB(originalRGB, errRGB, weight) {
    return [
        originalRGB[0] + (errRGB[0] * weight),
        originalRGB[1] + (errRGB[1] * weight),
        originalRGB[2] + (errRGB[2] * weight)
    ];
}

function rgbToLab(r, g, b) {
    r /= 255;
    g /= 255;
    b /= 255;

    r = r > 0.04045 ? Math.pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
    g = g > 0.04045 ? Math.pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
    b = b > 0.04045 ? Math.pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

    let x = r * 0.4124 + g * 0.3576 + b * 0.1805;
    let y = r * 0.2126 + g * 0.7152 + b * 0.0722;
    let z = r * 0.0193 + g * 0.1192 + b * 0.9505;

    x /= 0.95047;
    z /= 1.08883;

    let fx = x > 0.008856 ? Math.pow(x, 1 / 3) : (7.787 * x) + (16 / 116);
    let fy = y > 0.008856 ? Math.pow(y, 1 / 3) : (7.787 * y) + (16 / 116);
    let fz = z > 0.008856 ? Math.pow(z, 1 / 3) : (7.787 * z) + (16 / 116);

    return [
        (116 * fy) - 16,
        500 * (fx - fy),
        200 * (fy - fz)
    ];
}

let cacheHits = 0;

function getNear(r, g, b) {
    r = Math.round(r);
    g = Math.round(g);
    b = Math.round(b);

    let key = (r << 16) | (g << 8) | b;

    let best = rgbDistCache.get(key);
    // let best = rgbDistCache[key];

    if (best !== undefined) {
        cacheHits++;
        return best;
    } 

    best = 0;
    let bestDist = Infinity;
    let lab = rgbToLab(r, g, b);

    let i = 0;

    while (i < curPaletteLab.length) {
        let p = curPaletteLab[i];

        let dL = lab[0] - p[0];
        let da = lab[1] - p[1];
        let db = lab[2] - p[2];

        let checkDist = dL * dL + da * da + db * db;

        if (checkDist < bestDist) {
            bestDist = checkDist;
            best = i;
        }

        i++;
    }

    rgbDistCache.set(key, best);
    // rgbDistCache[key] = best;
    return best;
}

function hexToRgb(hex) {
    return [
        parseInt(hex.substring(1, 3), 16),
        parseInt(hex.substring(3, 5), 16),
        parseInt(hex.substring(5, 7), 16)
    ];
}

function preprocessImage() {
    imgW = epdData[epdIndex].width;
    imgH = epdData[epdIndex].height;

    let shiftX = parseInt(getElm("imgX").value);
    let shiftY = parseInt(getElm("imgY").value);
    let targetW = parseInt(getElm("imgW").value);
    let targetH = parseInt(getElm("imgH").value);
    let scaleMode = getElm("scaleMode").value;
    let rotation = parseInt(getElm("rotateMode").value);

    let srcW = srcImg.width;
    let srcH = srcImg.height;

    // rotated dimensions of the source image
    let rotW = srcW;
    let rotH = srcH;
    let rotTargetW = targetW;
    let rotTargetH = targetH;

    if (rotation === 90 || rotation === 270) {
        [rotW, rotH] = [rotH, rotW];
        [rotTargetW, rotTargetH] = [rotTargetH, rotTargetW];
    }

    let scale = 1;

    if (scaleMode === "fit")
        scale = Math.min(targetW / rotW, targetH / rotH);
    else if (scaleMode === "fill")
        scale = Math.max(targetW / rotW, targetH / rotH);
    else if (scaleMode === "original")
        scale = 1;

    let drawW = srcW * scale;
    let drawH = srcH * scale;
    let srcDrawW = srcW * Math.min(rotTargetW / drawW, 1);
    let srcDrawH = srcH * Math.min(rotTargetH / drawH, 1);
    drawW = Math.min(rotTargetW, drawW);
    drawH = Math.min(rotTargetH, drawH);

    let canvas = document.createElement("canvas");
    canvas.width = imgW;
    canvas.height = imgH;

    let ctx = canvas.getContext("2d");

    let bgHex = getElm("bgColour").value;
    ctx.fillStyle = bgHex;
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    ctx.save();

    ctx.translate(imgW / 2 + shiftX, imgH / 2 + shiftY);
    ctx.rotate(rotation * Math.PI / 180);


    ctx.drawImage(
        srcImg,
        (srcW - srcDrawW) / 2,
        (srcH - srcDrawH) / 2,
        srcDrawW,
        srcDrawH,
        -drawW / 2,
        -drawH / 2,
        drawW,
        drawH
    );

    ctx.restore();

    return ctx.getImageData(0, 0, canvas.width, canvas.height);
}

function processImg() {
    const timeStart = performance.now();
    cacheHits = 0;

    if (!srcImg) {
        console.log("Process image aborted, no source image.");
        return;
    }

    let srcImgData = preprocessImage();
    let srcW = srcImgData.width;
    let srcH = srcImgData.height;

    console.log(`Preprocess Duration: ${performance.now() - timeStart}ms`);

    if ((imgW < 3) || (imgH < 3)) {
        alert("Image is too small");
        return;
    }

    dstColourCodesBuffer = new Uint8Array(imgW * imgH);

    getElm("processedBox").classList.remove("hidden");
    let canvasElm = getElm("processedImg");

    canvasElm.width = imgW;
    canvasElm.height = imgH;
    dstImgData = new ImageData(imgW, imgH);

    let bgRGB = hexToRgb(getElm("bgColour").value);

    let pixelIndex = 0;

    if (!dithering) {
        let bgIndex = getNear(bgRGB[0], bgRGB[1], bgRGB[2]);
        for (let row = 0; row < imgH; row++) {
            if ((row < 0) || (row >= srcH)) {
                for (let x = 0; x < imgW; x++, pixelIndex++) setColourCode(pixelIndex, bgIndex);
                continue;
            }

            for (let col = 0; col < imgW; col++) {
                if ((col < 0) || (col >= srcW)) {
                    setColourCode(pixelIndex, bgIndex);
                    pixelIndex++;
                    continue;
                }

                let pos = (row * srcW + col) * 4;
                setColourCode(pixelIndex, getNear(srcImgData.data[pos], srcImgData.data[pos + 1], srcImgData.data[pos + 2]));
                pixelIndex++;
            }
        }
    } else { // Error-diffusion dithering
        let errRowA = 0;
        let errRowB = 1;
        let errBuffers = [Array.from({ length: imgW }, () => [0, 0, 0]), Array.from({ length: imgW }, () => [0, 0, 0])];

        for (let row = 0; row < imgH; row++) {
            [errRowA, errRowB] = [errRowB, errRowA];

            for (let col = 0; col < imgW; col++)
                errBuffers[errRowB][col] = [0, 0, 0];

            for (let col = 0; col < imgW; col++) {
                let srcRGB = [0, 0, 0];
                if ((col < 0) || (col >= srcW) || (row < 0) || (row >= srcH)) {
                    srcRGB = bgRGB;
                } else {
                    let pos = (row * srcW + col) * 4;
                    srcRGB = [
                        srcImgData.data[pos],
                        srcImgData.data[pos + 1],
                        srcImgData.data[pos + 2]
                    ]
                }

                let newRGB = [0, 0, 0];
                for (let k = 0; k < 3; k++) {
                    newRGB[k] = Math.max(0, Math.min(255, srcRGB[k] + errBuffers[errRowA][col][k]));
                }

                let colourIndex = getNear(newRGB[0], newRGB[1], newRGB[2]);

                setColourCode(pixelIndex, colourIndex);

                pixelIndex++;

                let errRGB = [
                    newRGB[0] - curPaletteRGB[colourIndex][0],
                    newRGB[1] - curPaletteRGB[colourIndex][1],
                    newRGB[2] - curPaletteRGB[colourIndex][2]
                ];

                if (errRGB[0] === 0 && errRGB[1] === 0 && errRGB[2] === 0) continue;
                if (row == imgH - 1) continue; // bottom edge

                if (!col) { // left edge
                    errBuffers[errRowA][col + 1] = getWeightedErrRGB(errBuffers[errRowA][col + 1], errRGB, 7 / 16); // right
                    errBuffers[errRowB][col + 1] = getWeightedErrRGB(errBuffers[errRowB][col + 1], errRGB, 2 / 16); // below-right
                    errBuffers[errRowB][col] = getWeightedErrRGB(errBuffers[errRowB][col], errRGB, 7 / 16); // below
                } else if (col == imgW - 1) { // right edge
                    errBuffers[errRowB][col] = getWeightedErrRGB(errBuffers[errRowB][col], errRGB, 9 / 16); // below
                    errBuffers[errRowB][col - 1] = getWeightedErrRGB(errBuffers[errRowB][col - 1], errRGB, 7 / 16); // below-left
                } else { // middle
                    errBuffers[errRowB][col - 1] = getWeightedErrRGB(errBuffers[errRowB][col - 1], errRGB, 3 / 16); // below-left
                    errBuffers[errRowB][col] = getWeightedErrRGB(errBuffers[errRowB][col], errRGB, 5 / 16); // below
                    errBuffers[errRowB][col + 1] = getWeightedErrRGB(errBuffers[errRowB][col + 1], errRGB, 1 / 16); // below-right
                    errBuffers[errRowA][col + 1] = getWeightedErrRGB(errBuffers[errRowA][col + 1], errRGB, 7 / 16); // right
                }
            }
        }
    }

    console.log(`Process Duration: ${performance.now() - timeStart}ms`);
    console.log(`Process RGB Cache Size: ${rgbDistCache.size}, Hits: ${cacheHits} (${((cacheHits / (imgW * imgH)) * 100).toFixed(2)}%)`);

    setTimeout(() => canvasElm.getContext("2d").putImageData(dstImgData, 0, 0), 100);
}

// Script D
let pxInd, stage;
const maxChunkSize = 1024;
let ws;
let commandQueue = [];
let queueIndex = 0;
let isProcessing = false;

function byteToStr(v) { return String.fromCharCode((v & 0xF) + 97, ((v >> 4) & 0xF) + 97); }
function wordToStr(v) { return byteToStr(v & 0xFF) + byteToStr((v >> 8) & 0xFF); }


function enqueueCommand(cmdData, logMsg, progress) {
    commandQueue.push({ payload: cmdData, log: logMsg, prog: progress });
}

function advanceQueue(q = 0) {
    console.log(`Request: ${q + 1} / ${commandQueue.length}`);
    if (q >= commandQueue.length) {
        console.log("End...");
        isProcessing = false;
        return;
    }

    let cmd = commandQueue[q];
    setInn("logTag", cmd.log);
    document.querySelector("#logProgress").style.width = cmd.prog + "%";
    ws.send(cmd.payload);
    if (reqTimeout) console.log("repeated.");
    clearTimeout(reqTimeout);
    reqTimeout = setTimeout(() => advanceQueue(q), 1000);
}

const COLOURR_TYPE = {
    FOUR_BYTE: -2,
    TWO_BYTE: -1,
    ONE_BYTE: 0,
}

function EPDSendChunk(colourData, colourType, startProg, endProg, excludeColour = 0) {
    while (pxInd < colourData.length) {
        let msgData = "";
        if (colourType == COLOURR_TYPE.FOUR_BYTE) { // 4-byte colours
            while ((pxInd < colourData.length) && (msgData.length < maxChunkSize)) {
                let v = 0;
                for (let i = 0; i < 16; i += 4)
                    if (pxInd < colourData.length)
                        v |= (colourData[pxInd++] << i);
                msgData += wordToStr(v);
            }
        } else if (colourType == COLOURR_TYPE.TWO_BYTE) { // 2-byte colours
            while ((pxInd < colourData.length) && (msgData.length < maxChunkSize)) {
                let v = 0;
                for (let i = 0; i < 16; i += 2)
                    if (pxInd < colourData.length)
                        v |= (colourData[pxInd++] << i);
                msgData += wordToStr(v);
            }
        } else if (colourType == COLOURR_TYPE.ONE_BYTE) { // 1-byte colours
            while ((pxInd < colourData.length) && (msgData.length < maxChunkSize)) {
                let v = 0;
                for (let i = 0; i < 8; i++)
                    if ((pxInd < colourData.length) && (colourData[pxInd++] != excludeColour))
                        v |= (128 >> i);
                msgData += byteToStr(v);
            }
        } else {
            alert("ERROR: Invalid colour type in code.");
            return;
        }

        const progress = ((pxInd / colourData.length) * (endProg - startProg) + startProg);
        enqueueCommand("LOAD_" + msgData, `Sending Chunk: ${(Math.round(progress * 100) / 100).toFixed(2)}%`, progress);
    }
}

function uploadImage() {
    if (!dstColourCodesBuffer.length) { alert("Process image first."); return; }
    if (ws.readyState !== WebSocket.OPEN) { alert("Hardware disconnected."); return; }

    commandQueue = [];
    queueIndex = 0;
    isProcessing = true;

    console.log("Processing Uploads...");

    enqueueCommand("INIT_" + epdIndex, "Initialising Display", 1);

    if (epdIndex == 50) { // 13.3 6 colors (split 1200->600+600)
        let leftA = [], rightA = [];
        let w = dstImgData.width, h = dstImgData.height;
        for (let row = 0; row < h; row++) {
            let base = row * w;
            for (let xx = 0; xx < 600; xx++) leftA.push(dstColourCodesBuffer[base + xx]);
            for (let xx = 600; xx < w; xx++) rightA.push(dstColourCodesBuffer[base + xx]);
        }

        pxInd = 0;
        EPDSendChunk(leftA, COLOURR_TYPE.FOUR_BYTE, 1, 50);
        enqueueCommand("NEXT", "Switching Chip Select", 50);
        pxInd = 0;
        EPDSendChunk(rightA, COLOURR_TYPE.FOUR_BYTE, 50, 99);
        enqueueCommand("SHOW", "Displaying (DRF)", 100);
    }

    else if ([3, 39, 43].includes(epdIndex)) { // 2.13
        EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.ONE_BYTE, 1, 99);
        enqueueCommand("SHOW", "Displaying (DRF)", 100);
    }

    else if (epdIndex == 40) { // 2.13 B V4
        EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.ONE_BYTE, 1, 50);
        enqueueCommand("NEXT", "Switching Chip Select", 50);
        pxInd = 0;
        EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.ONE_BYTE, 50, 99, 3);
        enqueueCommand("SHOW", "Displaying (DRF)", 100);
    }

    else if ([0, 3, 6, 7, 9, 12, 16, 19, 22, 26, 27, 28].includes(epdIndex)) {
        EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.ONE_BYTE, 1, 99);
        enqueueCommand("SHOW", "Displaying (DRF)", 100);
    }

    else if (epdIndex > 15 && epdIndex < 22) {
        EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.TWO_BYTE, 1, 99);
        enqueueCommand("SHOW", "Displaying (DRF)", 100);
    }

    else if (epdIndex == 25 || epdIndex == 37) { // 7 colors
        EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.FOUR_BYTE, 1, 99);
        enqueueCommand("SHOW", "Displaying (DRF)", 100);
    }

    else if (epdIndex == 49) { // 6 colors
        EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.FOUR_BYTE, 1, 99);
        enqueueCommand("SHOW", "Displaying (DRF)", 100);
    }

    else {
        console.log("Unknown EPD index, uploading default protocol.");
        if (epdIndex == 23)
            EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.ONE_BYTE, 1, 99);
        else {
            EPDSendChunk(dstColourCodesBuffer, ([1, 12].includes(epdIndex)) ? COLOURR_TYPE.TWO_BYTE : COLOURR_TYPE.ONE_BYTE, 1, 50);
            enqueueCommand("NEXT", "Switching Chip Select", 50);
            EPDSendChunk(dstColourCodesBuffer, COLOURR_TYPE.ONE_BYTE, 50, 99, 3);
        }
        enqueueCommand("SHOW", "Displaying (DRF)", 100);

    }

    console.log("Uploading...");
    advanceQueue();
}

function clearImage() {
    if (ws.readyState !== WebSocket.OPEN) { alert("Hardware disconnected."); return; }

    commandQueue = [];
    queueIndex = 0;
    isProcessing = true;

    console.log("Processing Uploads...");
    enqueueCommand("INIT_" + epdIndex, "Initialising Display", 25);
    enqueueCommand("CLEAR", "Uploading Clear Image", 75);
    enqueueCommand("SHOW", "Displaying (DRF)", 100);

    console.log("Uploading...");
    advanceQueue();
}