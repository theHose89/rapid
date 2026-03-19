import Jimp from "jimp";

//<button id="convertButton" onclick="rgbVal(name)">Convert to ASCII </button>

function printAscii(imageData, width, height) {
    output = "";
    for (let i = 0; i < height; i++) {
    let row = "";
    for (let j = 0; j < width; j++) {
      const pixel = imageData[i * width + j];
      if (pixel === 255) {
        row += "- ";
      } else if (pixel === 0) {
        row += "@ ";
      } else {
        row += "? ";
      }
    }
    row += '\n';
    output += row;
  }

  return output;
}


const input = document.getElementById('imageUpload');
const preview = document.getElementById('preview');

  
  
const btn = document.getElementById("convertButton");
btn.onclick = async function ascii() {
  

    const imagePath = URL.createObjectURL(file);

  alert("Button was clicked!");
  try {
    const image = await Jimp.read(imagePath);
    image.grayscale();

    const width = image.width;
    const height = image.height;
    const imageData = new Uint8Array(width * height);

    for (let i = 0; i < height; i++) {
      for (let j = 0; j < width; j++) {
        const pixel = image.getPixelColor(j, i);
        imageData[i * width + j] = (pixel >> 24) & 0xff; // red channel = gray after grayscale()
      }
    }

    output = printAscii(imageData, width, height);
  } catch (err) {
    console.error("Failed to load image", err.message);
    return output;
  }
}

async function rgbVal(path) {
  const imagePath = path;

  try {
    const image = await Jimp.read(imagePath);

    const width = image.width;
    const height = image.height;
    const imageData = new Uint8Array(width * height);

    output = "";
    for (let i = 0; i < height*5; i++) {
        let row = "";
        for (let j = 0; j < width; j++) {
            const pixel = image.getPixelColor(j, i);
            const rgba = Jimp.intToRGBA(pixelColorInt);
            if(height % 4 === 0){
                row += rgba.r;
            }else if(height % 4 === 1){
                row += rgba.g;
            }else if(height % 4 === 2){
                row += rgba.b;
            }else if(height % 4 === 3){
                row += rgba.a;
            }
        }
        row += '\n';
        output += row;
    }

    return output;
  } catch (err) {
    console.error("Failed to load image", err.message);
    process.exit(1);
  }
}



function myFunction() {
  console.log("Button was clicked!");
}