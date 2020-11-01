from customer import Customer

import psycopg2

from config import read_config
from messages import *

POSTGRESQL_CONFIG_FILE_NAME = "database.cfg"

"""
    Connects to PostgreSQL database and returns connection object.
"""


def connect_to_db():
    db_conn_params = read_config(filename=POSTGRESQL_CONFIG_FILE_NAME, section="postgresql")
    conn = psycopg2.connect(**db_conn_params)
    conn.autocommit = False
    return conn


"""
    Splits given command string by spaces and trims each token.
    Returns token list.
"""


def tokenize_command(command):
    tokens = command.split(" ")
    return [t.strip() for t in tokens]


"""
    Prints list of available commands of the software.
"""


def help():
    # prints the choices for commands and parameters
    print("\n*** Please enter one of the following commands ***")
    print("> help")
    print("> sign_up <email> <password> <first_name> <last_name> <plan_id>")
    print("> sign_in <email> <password>")
    print("> sign_out")
    print("> show_plans")
    print("> show_subscription")
    print("> subscribe <plan_id>")
    print("> watched_movies <movie_id_1> <movie_id_2> <movie_id_3> ... <movie_id_n>")
    print("> search_for_movies <keyword_1> <keyword_2> <keyword_3> ... <keyword_n>")
    print("> suggest_movies")
    print("> quit")


"""
    Saves customer with given details.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
"""

# TODO : fix all exceptions!!!
# TODO : correct rating value -> .1f !!!


def sign_up(conn, email, password, first_name, last_name, plan_id):
    # TODO: DONE!
    cursor = conn.cursor()

    query = """INSERT INTO customer(email, password, first_name, last_name, session_count, plan_id)
    VALUES(""" + "'" +  email + "', '" + password + "', '" + first_name + "', '" + last_name + "', " + " 0," + plan_id + ");"

    try:
        cursor.execute(query)
        conn.commit()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        conn.rollback()
        return False, CMD_EXECUTION_FAILED
"""
    Retrieves customer information if email and password is correct and customer's session_count < max_parallel_sessions.
    - Return type is a tuple, 1st element is a customer object and 2nd element is the response message from messages.py.
    - If email or password is wrong, return tuple (None, USER_SIGNIN_FAILED).
    - If session_count < max_parallel_sessions, commit changes (increment session_count) and return tuple (customer, CMD_EXECUTION_SUCCESS).
    - If session_count >= max_parallel_sessions, return tuple (None, USER_ALL_SESSIONS_ARE_USED).
    - If any exception occurs; rollback, do nothing on the database and return tuple (None, USER_SIGNIN_FAILED).
"""


def sign_in(conn, email, password):
    # TODO: DONE!
    cursor = conn.cursor()

    userCheckQuery = (
        """ Select
                c.customer_id,
                c.first_name,
                c.last_name,
                c.session_count,
                c.plan_id,
                p.max_parallel_sessions
            From
                customer c,
                plan p
            where
                c.email = %s
                and c.password = %s
                and p.plan_id = c.plan_id"""
    )

    incrementSessionCountQuery = (
        " UPDATE customer\n"
        "                    SET session_count = session_count+1\n"
        "                    WHERE customer_id = %s"
    )

    try:
        cursor.execute(userCheckQuery, (email, password))
        result = cursor.fetchall()
        customerID, firstName, lastName, sessionCount, planID, maxParallelSessions = result[0]
        if sessionCount < maxParallelSessions:
            try:
                cursor.execute(incrementSessionCountQuery, [customerID])
                conn.commit()
                customer = Customer(customerID, email, firstName, lastName, sessionCount, planID)
                return customer, CMD_EXECUTION_SUCCESS
            except Exception as e:
                conn.rollback()
                return None, USER_SIGNIN_FAILED
        else:
            return None, USER_ALL_SESSIONS_ARE_USED
    except Exception as e:
        conn.rollback()
        return None, USER_SIGNIN_FAILED


"""
    Signs out from given customer's account.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - Decrement session_count of the customer in the database.
    - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
"""


def sign_out(conn, customer):
    # TODO: DONE!
    cursor = conn.cursor()

    decrementSessionCountQuery = (
        " UPDATE customer\n"
        " SET session_count = session_count-1\n"
        " WHERE customer_id = %s"
    )

    getSessionCountQuery = (
        "Select "
            "c.session_count "
        "From "
            "customer c "
        "Where "
            "c.customer_id = %s "
    )

    try:
        cursor.execute(getSessionCountQuery, [customer.customer_id])
        result = cursor.fetchall()
        if result[0][0] > 0:
            cursor.execute(decrementSessionCountQuery, [customer.customer_id])
            conn.commit()
            return True, CMD_EXECUTION_SUCCESS
        else:
            return False, CMD_EXECUTION_FAILED
    except Exception as e:
        conn.rollback()
        return False, CMD_EXECUTION_FAILED


"""
    Quits from program.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - Remember to sign authenticated user out first.
    - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
"""


def quit(conn, customer):
    # TODO: DONE!
    if customer is None:
        return True, CMD_EXECUTION_SUCCESS
    exec_status, exec_message = sign_out(conn, customer)
    if exec_status:
        try:
            conn.commit()
            return True, CMD_EXECUTION_SUCCESS
        except Exception as e:
            conn.rollback()
        return False, CMD_EXECUTION_FAILED
    else:
        return False, CMD_EXECUTION_FAILED


"""
    Retrieves all available plans and prints them.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - If the operation is successful; print available plans and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

    Output should be like:
    #|Name|Resolution|Max Sessions|Monthly Fee
    1|Basic|720P|2|30
    2|Advanced|1080P|4|50
    3|Premium|4K|10|90
"""


def show_plans(conn):
    # TODO: DONE!
    cursor = conn.cursor()

    retrievePlansQuery = (
        " Select *"
        " From plan"
        " ORDER BY plan_id "
    )

    try:
        cursor.execute(retrievePlansQuery)
        result = cursor.fetchall()
        print("#|Name|Resolution|Max Sessions|Monthly Fee")
        for plan in result:
            print("{id}|{Name}|{Resolution}|{Max_Sessions}|{Monthly_Fee}"
                  .format(id=plan[0], Name=plan[1], Resolution=plan[2], Max_Sessions=plan[3], Monthly_Fee=plan[4]))
        conn.commit()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        conn.rollback()
        return False, CMD_EXECUTION_FAILED


"""
    Retrieves authenticated user's plan and prints it. 
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - If the operation is successful; print the authenticated customer's plan and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

    Output should be like:
    #|Name|Resolution|Max Sessions|Monthly Fee
    1|Basic|720P|2|30
"""


def show_subscription(conn, customer):
    # TODO: DONE!
    cursor = conn.cursor()

    subcriptionQuery = (
        "Select "
            "p.plan_id, "
            "p.plan_name, "
            "p.resolution, "
            "p.max_parallel_sessions, "
            "p.monthly_fee "
        "From "
            "plan p, "
            "customer c "
        "Where "
            "p.plan_id = c.plan_id "
            "and c.customer_id = %s "
    )

    try:
        cursor.execute(subcriptionQuery, [customer.customer_id])
        result = cursor.fetchall()
        print("#|Name|Resolution|Max Sessions|Monthly Fee")
        print("{id}|{Name}|{Resolution}|{Max_Sessions}|{Monthly_Fee}"
              .format(id=result[0][0], Name=result[0][1], Resolution=result[0][2], Max_Sessions=result[0][3], Monthly_Fee=result[0][4]))
        conn.commit()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        conn.rollback()
        return False, CMD_EXECUTION_FAILED

"""
    Insert customer-movie relationships to Watched table if not exists in Watched table.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - If a customer-movie relationship already exists, do nothing on the database and return (True, CMD_EXECUTION_SUCCESS).
    - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any one of the movie ids is incorrect; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
    - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
"""


def watched_movies(conn, customer, movie_ids):
    # TODO: DONE!

    cursor = conn.cursor()

    retrieveMoviesQuery = (
        "Select "
            "w.movie_id "
        "From "
            "watched w "
        "Where "
            "w.customer_id = %s "
    )

    insertMovieQuery = (
        "INSERT INTO watched(customer_id, movie_id) "
        "VALUES (%s, %s)"
    )

    checkMovieQuery = (
        "Select * "
        "From "
            "movies m "
        "Where "
            "m.movie_id = %s "
    )

    try:
        cursor.execute(retrieveMoviesQuery, [customer.customer_id])
        result = cursor.fetchall()
        watchedMovies = []
        for ele in result:
            watchedMovies.append(ele[0])
        for movie in movie_ids:
            if movie in watchedMovies:
                continue
            cursor.execute(checkMovieQuery, [movie])
            result2 = cursor.fetchall()
            if result2:
                cursor.execute(insertMovieQuery, (customer.customer_id, movie))
            else:
                conn.rollback()
                return False, CMD_EXECUTION_FAILED
        conn.commit()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        conn.rollback()
        return False, CMD_EXECUTION_FAILED


"""
    Subscribe authenticated customer to new plan.
    - Return type is a tuple, 1st element is a customer object and 2nd element is the response message from messages.py.
    - If target plan does not exist on the database, return tuple (None, SUBSCRIBE_PLAN_NOT_FOUND).
    - If the new plan's max_parallel_sessions < current plan's max_parallel_sessions, return tuple (None, SUBSCRIBE_MAX_PARALLEL_SESSIONS_UNAVAILABLE).
    - If the operation is successful, commit changes and return tuple (customer, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; rollback, do nothing on the database and return tuple (None, CMD_EXECUTION_FAILED).
"""


def subscribe(conn, customer, plan_id):
    # TODO: DONE!
    cursor = conn.cursor()

    getMaxAllowedUsersQuery = (
        "Select "
            "p.max_parallel_sessions "
        "From "
            "plan p, "
            "customer c "
        "Where "
            "p.plan_id = c.plan_id "
            "and c.customer_id = %s "
    )

    getPlanMaxAllowedUsersQuery = (
        "Select "
            "p.max_parallel_sessions "
        "From "
            "plan p "
        "Where "
            "p.plan_id = %s "
    )

    updateSubscriptionQuery = (
        " UPDATE customer\n"
        " SET plan_id = %s\n"
        " WHERE customer_id = %s"
    )

    try:
        cursor.execute(getMaxAllowedUsersQuery, [customer.customer_id])
        result = cursor.fetchall()
        currentMaxAllowedUserNumber = result[0][0]
    except Exception as e:
        conn.rollback()
        return False, CMD_EXECUTION_FAILED
    try:
        cursor.execute(getPlanMaxAllowedUsersQuery, [plan_id])
        result = cursor.fetchall()
        planMaxAllowedUserNumber = result[0][0]
    except Exception as e:
        conn.rollback()
        return None, SUBSCRIBE_PLAN_NOT_FOUND
    if currentMaxAllowedUserNumber>planMaxAllowedUserNumber:
        return None, SUBSCRIBE_MAX_PARALLEL_SESSIONS_UNAVAILABLE
    else:
        try:
            cursor.execute(updateSubscriptionQuery, (plan_id, customer.customer_id))
            customer.plan_id = plan_id
            conn.commit()
            return customer, CMD_EXECUTION_SUCCESS
        except Exception as e:
            conn.rollback()
            return False, CMD_EXECUTION_FAILED

"""
    Searches for movies with given search_text.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - Print all movies whose titles contain given search_text IN CASE-INSENSITIVE MANNER.
    - If the operation is successful; print movies found and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

    Output should be like:
    Id|Title|Year|Rating|Votes|Watched
    "tt0147505"|"Sinbad: The Battle of the Dark Knights"|1998|2.2|149|0
    "tt0468569"|"The Dark Knight"|2008|9.0|2021237|1
    "tt1345836"|"The Dark Knight Rises"|2012|8.4|1362116|0
    "tt3153806"|"Masterpiece: Frank Millers The Dark Knight Returns"|2013|7.8|28|0
    "tt4430982"|"Batman: The Dark Knight Beyond"|0|0.0|0|0
    "tt4494606"|"The Dark Knight: Not So Serious"|2009|0.0|0|0
    "tt4498364"|"The Dark Knight: Knightfall - Part One"|2014|0.0|0|0
    "tt4504426"|"The Dark Knight: Knightfall - Part Two"|2014|0.0|0|0
    "tt4504908"|"The Dark Knight: Knightfall - Part Three"|2014|0.0|0|0
    "tt4653714"|"The Dark Knight Falls"|2015|5.4|8|0
    "tt6274696"|"The Dark Knight Returns: An Epic Fan Film"|2016|6.7|38|0
"""


def search_for_movies(conn, customer, search_text):
    # TODO: DONE!
    cursor = conn.cursor()
    searchText = "%" + search_text.lower() + "%"
    searchForMoviesQuery = (
        "Select * "
        "From "
            "movies m "
        "Where "
            "lower(title) like %s "
        " ORDER BY m.movie_id "
    )

    isSeenByUSerQuery = (
        "Select "
            "w.customer_id "
        "From "
            "watched w "
        "Where "
            "w.movie_id = %s "
        "and w.customer_id = %s"
    )


    try:
        cursor.execute(searchForMoviesQuery, [searchText])
        result = cursor.fetchall()
        if result:
            print("Id|Title|Year|Rating|Votes|Watched")
            for movie in result:
                cursor.execute(isSeenByUSerQuery, (movie[0], customer.customer_id))
                isSeen = cursor.fetchall()
                if isSeen:
                    watched = 1
                else:
                    watched = 0
                print("{id}|{Title}|{Year}|{Rating}|{Votes}|{Watched}"
                      .format(id=movie[0], Title=movie[1], Year=movie[2], Rating=movie[3], Votes=movie[4], Watched=watched))
            conn.commit()
            return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        conn.rollback()
        return False, CMD_EXECUTION_FAILED


"""
    Suggests combination of these movies:
        1- Find customer's genres. For each genre, find movies with most number of votes among the movies that the customer didn't watch.

        2- Find top 10 movies with most number of votes and highest rating, such that these movies are released 
           after 2010 ( [2010, today) ) and the customer didn't watch these movies.
           (descending order for votes, descending order for rating)

        3- Find top 10 movies with votes higher than the average number of votes of movies that the customer watched.
           Disregard the movies that the customer didn't watch.
           (descending order for votes)

    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.    
    - Output format and return format are same with search_for_movies.
    - Order these movies by their movie id, in ascending order at the end.
    - If the operation is successful; print movies suggested and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).
"""


def get_movie_id(movie):
    return movie[0]


def suggest_movies(conn, customer):
    # TODO: DONE!
    cursor = conn.cursor()

    step1Query = (
        """ WITH genres_table AS
            (SELECT DISTINCT
                g.genre_name
            FROM
                genres g,
                watched w
            WHERE
                w.customer_id = %s
                and w.movie_id = g.movie_id),
            seen_movies_table AS
            (SELECT
                m.movie_id
            FROM
                movies m,
                watched w
            WHERE
                w.customer_id = %s
                and w.movie_id = m.movie_id),
             max_votes_by_genre AS
            (SELECT
                g2.genre_name as genre_name,
                max(m2.votes) as max_votes
            FROM
                movies m2,
                genres g2,
                genres_table g3
            WHERE m2.movie_id NOT IN (  SELECT s.movie_id
                                        FROM seen_movies_table s)
                and m2.movie_id = g2.movie_id
                and g2.genre_name = g3.genre_name
            GROUP BY
                g2.genre_name)
            SELECT
                m3.movie_id,
                m3.title,
                m3.movie_year,
                m3.rating,
                m3.votes
            FROM
                movies m3,
                max_votes_by_genre v,
                genres g5
            WHERE
                v.genre_name = g5.genre_name
                and g5.movie_id = m3.movie_id
                and v.max_votes = m3.votes"""
    )

    step2Query = (
        """WITH seen_movies_table AS
            (SELECT
                m.movie_id
            FROM
                movies m,
                watched w
            WHERE
                w.customer_id = %s
                and w.movie_id = m.movie_id)
            SELECT
                *
            FROM
                movies m2
            WHERE m2.movie_id NOT IN (  SELECT s.movie_id
                                        FROM seen_movies_table s)
                and m2.movie_year >= 2010
            ORDER BY
                m2.votes DESC ,
                m2.rating DESC
            FETCH FIRST 10 ROWS ONLY"""
    )

    step3Query = (
        """WITH seen_movies_table AS
            (SELECT
                m.movie_id
            FROM
                movies m,
                watched w
            WHERE
                w.customer_id = %s
                and w.movie_id = m.movie_id),
            avg_table AS
            (SELECT
                avg(m.votes) as average
            FROM
                movies m,
                watched w
            WHERE
                w.customer_id = %s
                and w.movie_id = m.movie_id
            GROUP BY
                w.customer_id)
            SELECT
                m3.movie_id,
                m3.title,
                m3.movie_year,
                m3.rating,
                m3.votes
            FROM
                movies m3,
                avg_table a
            WHERE
                m3.votes > a.average
                and m3.movie_id NOT IN (SELECT s.movie_id
                                        FROM seen_movies_table s)
            ORDER BY
                m3.votes DESC
            FETCH FIRST 10 ROWS ONLY"""
    )
    try:
        cursor.execute(step1Query, (customer.customer_id, customer.customer_id))
        step1Result = cursor.fetchall()
        cursor.execute(step2Query, [customer.customer_id])
        step2Result = cursor.fetchall()
        cursor.execute(step3Query, (customer.customer_id, customer.customer_id))
        step3Result = cursor.fetchall()
        result = step1Result + step2Result + step3Result
        result = list(dict.fromkeys(result))
        result.sort(key=get_movie_id)
        print("Id|Title|Year|Rating|Votes")
        for movie in result:
            print("{id}|{Title}|{Year}|{Rating}|{Votes}"
                  .format(id=movie[0], Title=movie[1], Year=movie[2], Rating=movie[3], Votes=movie[4]))
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        conn.rollback()
        return False, CMD_EXECUTION_FAILED
