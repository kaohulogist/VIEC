import tkinter as tk
from random import randint

window = tk.Tk()
window.geometry('400x300')
def handle_keypress(event):
    print(event.char)

window.bind("<Key>", handle_keypress)
window.title("HEC5 UT Tyler-TSGC NASA 2022")

greeting = tk.Label(
    text="System Indication for Controllers",
    foreground="white",
    background="black",
)
greeting.grid(row=0,column=0,columnspan=3)
#greeting.pack()

frame = tk.Frame(relief="groove",borderwidth=5)
#frame.pack()

frame_status = tk.Frame(relief="groove",borderwidth=5)
#frame_status.pack()

# label controller 1, 2, 3 , 4
controller1 = tk.Label(
    text="Accerleromter Application's status at position 1:",
    pady=10, padx=20,
    justify= "right"
)
controller1.grid(row=1,column=0)
#controller1.pack()

controller2 = tk.Label(
    text="      Barometer Application's status at position 2:",
    pady=10, padx=20,
    justify= "left"
)
#controller2.pack()
controller2.grid(row=2,column=0)

controller3 = tk.Label(
    text="       Ultrasonic Application's status at position 3: ",
    pady=10, padx=20,
    justify= "left"
)
#controller3.pack()
controller3.grid(row=3,column=0)

controller4 = tk.Label(
    text="             Switch Application's status at position 4: ",
    pady=10, padx=20,
    justify= "left"
)
#controller4.pack()
controller4.grid(row=4,column=0)

# Label controller 1's status
controller1_status = tk.Label(
    text="ON / OFF ",
    pady=10, padx=0,
    justify= "left"
)
controller1_status.grid(row=1,column=1)

# Labe2 controller 2's status
controller2_status = tk.Label(
    text="ON / OFF ",
    pady=10, padx=0,
    justify= "left"
)
controller2_status.grid(row=2,column=1)

# Label controller 3's' status
controller3_status = tk.Label(
    text="ON / OFF ",
    pady=10, padx=0,
    justify= "left"
)
controller3_status.grid(row=3,column=1)
# Label controller 4's' status
controller4_status = tk.Label(
    text="ON / OFF ",
    pady=10, padx=0,
    justify= "left"
)
controller4_status.grid(row=4,column=1)

lab = tk.Label(text= randint(0,1000))
#lab.pack()
lab.grid(row=5,column=0,columnspan=2)
def update():
    lab['text'] = "System refreshes every 1000ms ( last refresh was " + str(randint(0,1000)) + "ms)",
    window.after(1000, update)
update()

def handle_click(event):
    print("The manual refresh operated!")

'''
refresh_button = tk.Button(
    text="Click to refresh manually!",
    width=30,
    height=1,
    bg="orange",
    fg="blue",
    command= window.update
)
refresh_button.bind("<Button-1>", handle_click)
#refresh_button.pack(pady=10)
refresh_button.grid(row=6,column=0)
'''

exit_button = tk.Button(window, text="Exit", command=window.destroy)
#exit_button.pack(pady=20)
exit_button.grid(row=7,column=0,pady=20,columnspan=2)

window.mainloop()