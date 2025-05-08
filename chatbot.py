import streamlit as st
from nltk.chat.util import Chat, reflections

# Movie data
movies = {
    'Interstellar': ['10:00 AM', '2:00 PM', '6:00 PM'],
    'The Dark Knight': ['11:00 AM', '3:00 PM', '7:00 PM'],
    'Dune': ['9:30 AM', '1:30 PM', '5:30 PM']
}

# Chat patterns
patterns = [
    (r'hi|hello|hey', ['Hello! How can I assist you today?']),
    (r'how are you', ['I am just a bot, but always ready to help!']),
    (r'(.*) movie', [f"Available movies: {', '.join(movies)}"]),
    (r'(.*) ticket', ['How many tickets would you like to book?']),
    (r'(.*) showtime|timing', ["Showtimes:\n" + '\n'.join(f"{m}: {', '.join(t)}" for m, t in movies.items())]),
    (r'(.*) book tickets', ["Great! Let's proceed with booking."]),
    (r'(.*)(bye|goodbye)', ['Thanks for visiting! Enjoy your movie.']),
]

chatbot = Chat(patterns, reflections)

# Booking logic
def book_tickets(movie, tickets, showtime):
    try:
        total = int(tickets) * 100
        return f"🎟 Booking confirmed!\n{tickets} tickets for '{movie}' at {showtime}.\nTotal: ₹{total}"
    except:
        return "❌ Please enter a valid number of tickets."

# Streamlit setup
st.set_page_config(page_title="🎬 Movie Ticket ChatBot")
st.title("🎬 Movie Ticket Booking ChatBot")
     
# Session state
if "chat" not in st.session_state: st.session_state.chat = []
if "booking_mode" not in st.session_state: st.session_state.booking_mode = False
if "step" not in st.session_state: st.session_state.step = 0
if "temp_data" not in st.session_state: st.session_state.temp_data = {}

# Chat display
for sender, message in st.session_state.chat:
    st.markdown(f"**{sender}:** {message}")

# User input
with st.form("chat_form", clear_on_submit=True):
    user_input = st.text_input("Type your message...")
    submitted = st.form_submit_button("Send")

if submitted and user_input:
    st.session_state.chat.append(("You", user_input))
    msg = user_input.strip()

    if st.session_state.booking_mode:
        step = st.session_state.step
        data = st.session_state.temp_data

        if step == 1:
            if msg not in movies:
                bot_reply = "Choose from: " + ', '.join(movies)
            else:
                data["movie"] = msg
                st.session_state.step = 2
                bot_reply = "How many tickets?"
        elif step == 2:
            data["tickets"] = msg
            st.session_state.step = 3
            times = '\n'.join(movies[data["movie"]])
            bot_reply = f"What showtime for '{data['movie']}'?\nOptions:\n{times}"
        elif step == 3:
            data["showtime"] = msg
            bot_reply = book_tickets(**data)
            st.session_state.booking_mode = False
            st.session_state.step = 0
            st.session_state.temp_data = {}
    elif "book tickets" in msg.lower():
        st.session_state.booking_mode = True
        st.session_state.step = 1
        st.session_state.temp_data = {}
        bot_reply = "Which movie would you like to watch?"
    else:
        bot_reply = chatbot.respond(msg) or "Sorry, I didn't understand that."

    st.session_state.chat.append(("Bot", bot_reply))
    st.rerun()

# Reset chat
st.divider()
if st.button("🗑 Reset Chat"):
    st.session_state.chat = []
    st.session_state.booking_mode = False
    st.session_state.step = 0
    st.session_state.temp_data = {}
    st.rerun()