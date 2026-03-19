import Jimp from "jimp";

function printAscii(imageData, width, height) {
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
    console.log(row);
  }
}

async function main() {
  const args = process.argv.slice(2);
  if (args.length === 0) {
    console.error("Usage: node main.js <image_path>");
    process.exit(1);
  }

  const imagePath = args[0];

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

    printAscii(imageData, width, height);
  } catch (err) {
    console.error("Failed to load image:", err.message);
    process.exit(1);
  }
}

main();