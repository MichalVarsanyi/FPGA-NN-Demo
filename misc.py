import torch

def evaluate(model, loader, criterion, device):
    # Evaluation mode
    model.eval()
    total_loss = 0
    correct = 0
    total = 0

    with torch.no_grad():
        # x are the images of a batch and y are the labels
        for x, y in loader:
            x, y = x.to(device), y.to(device)

            # We predict the labels by using doing a forward pass through the model
            out = model(x)
            # We calculate the loss by comparing the predicted labels with the true labels
            loss = criterion(out, y)
            # We accumulate the loss for all batches
            total_loss += loss.item()

            # We take the argument of the maximum logits through all images in the current batch
            # Preds is a vector of the predicted labels for the entire batch
            preds = out.argmax(dim=1)
            correct += (preds == y).sum().item()
            total += y.size(0)

    # Average batch loss (divide by total number of batches)
    avg_loss = total_loss / len(loader)
    accuracy = correct / total
    return avg_loss, accuracy
