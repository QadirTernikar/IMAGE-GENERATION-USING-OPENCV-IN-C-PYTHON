import cv2
import numpy as np

class ImageProcessor:
    @staticmethod
    def applyGrayscale(image):
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        return cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)  # Convert back to BGR for consistency

    @staticmethod
    def applySobelEdgeDetection(image):
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        grad_x = cv2.Sobel(gray, cv2.CV_16S, 1, 0, ksize=3, scale=1, delta=0, borderType=cv2.BORDER_DEFAULT)
        abs_grad_x = cv2.convertScaleAbs(grad_x)

        grad_y = cv2.Sobel(gray, cv2.CV_16S, 0, 1, ksize=3, scale=1, delta=0, borderType=cv2.BORDER_DEFAULT)
        abs_grad_y = cv2.convertScaleAbs(grad_y)

        grad = cv2.addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0)

        return cv2.cvtColor(grad, cv2.COLOR_GRAY2BGR)

def displayMenu():
    print("\nImage Processing Application")
    print("1. Load Image")
    print("2. Save Image")
    print("3. Apply Grayscale Filter")
    print("4. Apply Sobel Edge Detection")
    print("5. Exit")
    return int(input("Enter your choice: "))

def main():
    img = None
    filename = ""
    choice = 0

    while choice != 5:
        choice = displayMenu()

        if choice == 1:
            filename = input("Enter filename to load: ")
            img = cv2.imread(filename)
            if img is None:
                print(f"Error loading image {filename}")
            else:
                print("Image loaded successfully.")
        elif choice == 2:
            if img is not None:
                filename = input("Enter filename to save: ")
                if cv2.imwrite(filename, img):
                    print(f"Image saved successfully to {filename}")
                else:
                    print(f"Error saving image {filename}")
            else:
                print("No image loaded.")
        elif choice == 3:
            if img is not None:
                img = ImageProcessor.applyGrayscale(img)
                print("Applied grayscale filter.")
            else:
                print("No image loaded.")
        elif choice == 4:
            if img is not None:
                img = ImageProcessor.applySobelEdgeDetection(img)
                print("Applied Sobel edge detection.")
            else:
                print("No image loaded.")
        elif choice == 5:
            print("Exiting...")
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
