Installation

Clone the repository
bashgit clone https://github.com/yourusername/activity-booking-api.git
cd activity-booking-api

Install dependencies
bash npm install


Environment Variables

Create a .env file in the root directory with the following variables:
MONGO_URI=your_mongodb_connection_string
JWT_SECRET=your_jwt_secret
PORT=5000

Replace your_mongodb_connection_string with your MongoDB connection URI
Replace your_jwt_secret with a secure random string for JWT token generation



Running the Application

Start the server
bashnpm start
For development with automatic restart:
bashnpm run dev

Access the API
Once the server is running, you can access the API at:
http://localhost:5000
