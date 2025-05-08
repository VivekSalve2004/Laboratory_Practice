def get_reason(event: str) -> str:
    day = input("Enter the day of the week: ").strip().lower()
    if event == "water":
        if day == "monday":
            return "Water supply was cut due to scheduled maintenance on Monday."
        else:
            return "Water supply was fine. No known issues reported."
    elif event == "light":
        power_issue = input("Was there a power issue? (yes/no): ").strip().lower()
        if power_issue == "yes":
            return "No lights due to power outage in the common area."
        else:
            return "Lights were off due to blown fuse or maintenance work."
    else:
        return "Invalid event."


print("🏢 Society Maintenance Expert System")
print("1. Water Supply Issue")
print("2. Light Issue")
choice = input("Select an issue to diagnose (1 or 2): ").strip()

if choice == "1":
    print(get_reason("water"))
elif choice == "2":
    print(get_reason("light"))
else:
    print("Invalid choice")
