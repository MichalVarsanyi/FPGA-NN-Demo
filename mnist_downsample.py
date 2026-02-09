import torch
from torchvision import datasets, transforms
import torchvision.transforms.functional as TF
import matplotlib.pyplot as plt
import random

# -----------------------------
# Downsampling Transformation
# -----------------------------
class Downsample:
    def __init__(self, threshold=0.5, out_size=5):
        self.threshold = threshold
        self.out_size = out_size

    def __call__(self, img):

        # 1. Crop to content
        # There is an issue whre 1 will get cropped to content and then 
        # resized to 5x5, making the one's span the entire 5x5 output
        img2d = img.squeeze(0)
        nonzero = img2d.nonzero(as_tuple=False)

        if nonzero.numel() == 0:
            cropped = img
        else:
            y_min, x_min = nonzero.min(dim=0).values
            y_max, x_max = nonzero.max(dim=0).values
            cropped = img[:, y_min:y_max+1, x_min:x_max+1]

        # 2. Bicubic resize
        resized = torch.nn.functional.adaptive_avg_pool2d(
            cropped,
            (self.out_size, self.out_size)
        )

        # 4. Final binarization
        # Not binarizing in the middle of the grayscale values
        # allows for better downsampling results
        resized = (resized > 0.4).float()
        return resized

# -----------------------------
# Pick random samples
# -----------------------------
num_samples = 19

def visualize_sample(mnist_original, mnist_processed, num_samples):
    indices = random.sample(range(len(mnist_original)), num_samples)

    # -----------------------------
    # Plot 2 x 8 grid
    # -----------------------------
    fig, axes = plt.subplots(2, num_samples, figsize=(num_samples * 2, 4))

    for col, idx in enumerate(indices):
        orig_img, label = mnist_original[idx]
        proc_img, _ = mnist_processed[idx]

        # Top row: original
        axes[0, col].imshow(orig_img.squeeze(), cmap="gray")
        axes[0, col].set_title(str(label))
        axes[0, col].axis("off")

        # Bottom row: processed
        axes[1, col].imshow(proc_img.squeeze(), cmap="gray")
        axes[1, col].axis("off")

    axes[0, 0].set_ylabel("Original\n28×28", fontsize=10)
    axes[1, 0].set_ylabel("Processed\n1-bit 5×5", fontsize=10)

    plt.tight_layout()
    plt.show()
