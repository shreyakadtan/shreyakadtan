from flask import Flask, render_template
import pandas as pd

app = Flask(__name__)

@app.route("/")
def index():
    data = pd.read_csv("StudentPerformanceFactors.csv")

    # Use numeric columns from Kaggle dataset
    avg_hours = round(data["Hours_Studied"].mean(), 2)
    avg_attendance = round(data["Attendance"].mean(), 2)
    avg_previous_scores = round(data["Previous_Scores"].mean(), 2)

    return render_template(
        "index.html",
        avg_hours=avg_hours,
        avg_attendance=avg_attendance,
        avg_previous_scores=avg_previous_scores
    )

if __name__ == "__main__":
    app.run(debug=True)
