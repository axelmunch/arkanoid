import tkinter as tk
from tkinter import filedialog

root = tk.Tk()
root.withdraw()


def select_file_load():
    file_path = filedialog.askopenfilename(
        title="(LOAD) Select a level", filetypes=[("Arkanoid level", "*.level")]
    )

    return file_path


def select_file_save():
    file_path = filedialog.asksaveasfilename(
        title="(SAVE) Select a level",
        filetypes=[("Arkanoid level", "*.level")],
        defaultextension=".png",
    )

    return file_path
