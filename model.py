import torch
import torch.nn as nn

class FPGAnet(nn.Module):
    def __init__(self):
        super().__init__()

        self.model = nn.Sequential(
            nn.Flatten(),          # (B, 1, 5, 5) → (B, 25)
            nn.Linear(25, 32),
            nn.ReLU(),
            nn.Linear(32, 16),
            nn.ReLU(),
            nn.Linear(16, 10)       # logits
        )

    def forward(self, x):
        return self.model(x)