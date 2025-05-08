def ask(question):
    return input(question + " ").lower().strip()


def recommend_book():
    domain = ask("What is your project domain? (AI, Web, Data Science, IoT)")
    level = ask("What is your desired complexity? (Beginner, Intermediate, Advanced)")
    type_ = ask("What type of project is it? (Research, Application, Hardware)")

    if domain == "ai":
        if type_ == "research":
            return "Recommended: 'Artificial Intelligence: A Modern Approach' by Russell & Norvig"
        elif type_ == "application":
            return "Recommended: 'Hands-On Machine Learning with Scikit-Learn and TensorFlow'"
        else:
            return "Recommended: 'AI for Robotics'"

    elif domain == "web":
        if level == "beginner":
            return "Recommended: 'HTML & CSS: Design and Build Websites'"
        elif level == "intermediate":
            return "Recommended: 'Eloquent JavaScript'"
        else:
            return "Recommended: 'Designing Web APIs'"

    elif domain == "data science":
        return "Recommended: 'Python for Data Analysis' by Wes McKinney"

    elif domain == "iot":
        return "Recommended: 'Internet of Things: A Hands-On Approach'"

    else:
        return "No recommendation found. Please refine your inputs."


print("📚 Expert System - Library Book Recommender")
print(recommend_book())
