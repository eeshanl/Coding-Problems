from collections import defaultdict, deque
from typing import List

########################################################################################################################
# Combine 2 sorted linkedlists

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
def mergeTwoLists(list1, list2):
    if list1 == None:
        return list2
    if list2 == None:
        return list1

    p1 = list1
    p2 = list2
    temp = None
    if p1.val < p2.val:
        temp = p1
        p1 = p1.next
    else:
        temp = p2
        p2 = p2.next

    rv = temp

    while (p1 != None and p2 != None):
        if p1.val < p2.val:
            temp.next = p1
            p1 = p1.next
        else:
            temp.next = p2
            p2 = p2.next
        temp = temp.next

    if (p1 == None):
        temp.next = p2
    elif (p2 == None):
        temp.next = p1

    return rv


#######################################################################################################################
# Two Sum

def twoSum(nums: List[int], target: int) -> List[int]:
    mapp = {}
    rv = []
    for i in range(len(nums)):
        mapp[nums[i]] = i

    for i in range(len(nums)):
        diff = target - nums[i]
        if diff in mapp and mapp[diff] != i:
            return [i, mapp[diff]]     

    return rv

#######################################################################################################################
# Currency Conversion Rates

def build_graph(conversion_rates):
    """
    Build a graph from the conversion rates.
    
    Args:
    conversion_rates (list): List of conversion rate dictionaries.
    
    Returns:
    dict: A dictionary representing the graph.
    """
    graph = defaultdict(list)
    for rate in conversion_rates:
        graph[rate['from']].append((rate['to'], rate['rate']))
    return graph

def find_conversion_rate(graph, from_currency, to_currency):
    """
    Find the conversion rate from one currency to another using BFS.
    
    Args:
    graph (dict): Graph representing conversion rates.
    from_currency (str): The currency to convert from.
    to_currency (str): The currency to convert to.
    
    Returns:
    float: The conversion rate from from_currency to to_currency.
    """
    queue = deque([(from_currency, 1.0)])
    visited = set()
    
    while queue:
        current_currency, current_rate = queue.popleft()
        
        if current_currency == to_currency:
            return current_rate
        
        visited.add(current_currency)
        
        for neighbor, rate in graph[current_currency]:
            if neighbor not in visited:
                queue.append((neighbor, current_rate * rate))
    
    # If no conversion found
    return None

def convert_currency(amount, from_currency, to_currency, conversion_rates):
    """
    Convert an amount from one currency to another.
    
    Args:
    amount (float): The amount to convert.
    from_currency (str): The currency to convert from.
    to_currency (str): The currency to convert to.
    conversion_rates (list): List of conversion rate dictionaries.
    
    Returns:
    float: The converted amount.
    """
    graph = build_graph(conversion_rates)
    rate = find_conversion_rate(graph, from_currency, to_currency)
    if rate:
        return amount * rate
    else:
        raise ValueError(f"Conversion rate from {from_currency} to {to_currency} not found.")


#######################################################################################################################
# Max concurrent promotions running

def _event_sort_key(event):
    # Sort by time first
    # If times are the same, 'end' event comes before 'start' event
    return (event[0], event[1] == 'end')

def max_promotions_running(promotions):
    # Create a list to store all events (start and end times)
    events = []
    for promotion in promotions:
        start, end = promotion
        events.append((start, 'start'))
        events.append((end, 'end'))
    
    # Sort events using the custom sort key
    events.sort(key=_event_sort_key)
    
    max_running = 0
    current_running = 0
    
    # Traverse through all events
    for event in events:
        if event[1] == 'start':
            current_running += 1
            max_running = max(max_running, current_running)
        else:
            current_running -= 1
    
    return max_running


#######################################################################################################################
# radio tower signal propagation

def propagate_direction(grid, reachable_towers, row, col, d_row, d_col):
    """
    Helper function to propagate signal in a specific direction.
    
    Args:
        grid (list): 2D list representing the area with towers and obstacles.
        reachable_towers (list): List to store the towers that the signal can reach.
        row (int): Current row position.
        col (int): Current column position.
        d_row (int): Direction to move in row (1 for down, -1 for up, 0 for no movement).
        d_col (int): Direction to move in column (1 for right, -1 for left, 0 for no movement).
    
    Returns:
        None
    """
    # Store the initial position
    start_row = row
    start_col = col

    while row < len(grid) and col < len(grid[0]) and row >= 0 and col >= 0 and grid[row][col] != 'obstacle':
        
        if grid[row][col] == 'tower' and (row, col) != (start_row, start_col):
            reachable_towers.append((row, col))  # Add the tower to the list
        
        row += d_row
        col += d_col

def propagate_signal(grid, start_row, start_col):
    """
    Function to propagate the signal from a radio tower in all four directions until it hits an obstacle or boundary.
    Return the list of towers that the signal can reach.
    
    :param grid: 2D list representing the area with towers and obstacles.
    :param start_row: Starting row of the radio tower.
    :param start_col: Starting column of the radio tower.
    :return: List of tuples representing towers that the signal can reach.
    """
    rows = len(grid)
    cols = len(grid[0])
    reachable_towers = []

    # Propagate in all four directions
    propagate_direction(grid, reachable_towers, start_row, start_col, -1, 0)  # Up
    propagate_direction(grid, reachable_towers, start_row, start_col, 1, 0)   # Down
    propagate_direction(grid, reachable_towers, start_row, start_col, 0, -1)  # Left
    propagate_direction(grid, reachable_towers, start_row, start_col, 0, 1)   # Right

    return reachable_towers

def find_reachable_towers(grid):
    """
    Find all towers and the towers they can reach with their signals.
    
    :param grid: 2D list representing the area with towers and obstacles.
    :return: Dictionary with tower positions as keys and lists of reachable tower positions as values.
    """
    rows = len(grid)
    cols = len(grid[0])
    tower_reach = {}

    for row in range(rows):
        for col in range(cols):
            if grid[row][col] == 'tower':
                reachable_towers = propagate_signal(grid, row, col)
                tower_reach[(row, col)] = reachable_towers

    return tower_reach


#######################################################################################################################
# Scrabble type game

def get_word_score(word, letter_scores):
    """
    Calculate the score of a word based on the given letter scores using a for loop.
    
    :param word: The word to calculate the score for.
    :param letter_scores: A dictionary mapping letters to their scores.
    :return: The total score of the word.
    """
    total_score = 0
    for letter in word:
        total_score += letter_scores[letter]
    return total_score

def generate_permutations(tiles, r):
    """
    Generate all possible permutations of a given length r from the tiles.
    
    :param tiles: A list of available letter tiles.
    :param r: The length of each permutation.
    :return: A list of permutations.
    """
    if r == 0:
        return [[]]
    
    permutations = []
    for i in range(len(tiles)):
        for perm in generate_permutations(tiles[:i] + tiles[i+1:], r - 1):
            permutations.append([tiles[i]] + perm)
    
    return permutations

def find_best_word(tiles, letter_scores, valid_words):
    """
    Find the best word that can be formed from the given tiles.
    
    :param tiles: A list of available letter tiles.
    :param letter_scores: A dictionary mapping letters to their scores.
    :param valid_words: A set of valid words.
    :return: The best word that can be formed, and its score.
    """
    best_word = ""
    best_score = 0
    
    # Generate all possible words from the given tiles
    for i in range(1, len(tiles) + 1):
        permutations = generate_permutations(tiles, i)
        for combo in permutations:
            word = ""
            for c in combo:
                word += c
            if word in valid_words:
                score = get_word_score(word, letter_scores)
                if score > best_score:
                    best_word = word
                    best_score = score
                    
    return best_word, best_score


#######################################################################################################################
# Group anagrams

def group_anagrams(strings):
    anagrams = {}

    for string in strings:
        sorted_string = ""
        for c in sorted(string):
            sorted_string += c

        if sorted_string not in anagrams:
            anagrams[sorted_string] = []
        anagrams[sorted_string].append(string)
    
    return list(anagrams.values())


#######################################################################################################################
# Next Greater Element

def next_greater_element(nums):
    mapp = {}
    for i in range(len(nums)):
        cur_min = float('inf')
        for j in range(i + 1, len(nums)):  # Find the next greater element
            if nums[j] > nums[i]:
                if nums[j] < cur_min:
                    cur_min = nums[j]

        if cur_min == float('inf'):
            mapp[nums[i]] = -1
        else:
            mapp[nums[i]] = cur_min

    return mapp


#######################################################################################################################
# Baby Blocks

def is_valid_combination(blocks, word, used_indices):
        if not word:
            return True
        
        first_letter = word[0]
        
        for i, block in enumerate(blocks):
            if i not in used_indices and first_letter in block:
                used_indices.add(i)
                if is_valid_combination(blocks, word[1:], used_indices):
                    return True
                used_indices.remove(i)
        
        return False

def can_spell_word(blocks, word):

    used_indices = set()
    return is_valid_combination(blocks, word, used_indices)


#######################################################################################################################
# Compound Words

def find_parts_helper(word, path, word_set, parts):
    """
    Recursive function to find all possible combinations of words in a given word.

    Args:
        word (str): The word to find combinations for.
        path (list): The current path of words.
        word_set (set): Set of words to check against.
        parts (list): List to store the found combinations.
    """
    # Base case: If the word is empty, check if the path is a compound word
    if not word:
        if len(path) > 1:  # Only consider it if it's actually a compound word
            parts.append(path[:])
        return
    
    # Iterate through possible prefixes of the word
    for i in range(1, len(word) + 1):
        prefix = word[:i]
        
        # If the prefix is in the word set, recursively find combinations with the remaining part of the word
        if prefix in word_set:
            find_parts_helper(word[i:], path + [prefix], word_set, parts)

def find_parts(word, word_set):
    parts = []
    find_parts_helper(word, [], word_set, parts)
    return parts

def find_compound_words(words):
    word_set = set(words)  # To allow for O(1) lookups
    compound_words = []

    for word in words:
        parts = find_parts(word, word_set)
        if parts:
            compound_words += parts

    return compound_words


#######################################################################################################################
# Currenty Denominations

def get_minimum_currency_denomination(amount):
    # Define the denominations
    denominations = [20, 10, 5, 1, 0.25, 0.1, 0.05, 0.01]

    # Initialize a dictionary to store the count of each denomination
    denomination_count = {}
    for denomination in denominations:
        denomination_count[denomination] = 0

    # Traverse through each denomination to calculate the number of each needed
    for denomination in denominations:
        if amount >= denomination:
            count = int(amount // denomination)
            amount -= count * denomination
            denomination_count[denomination] = count

    result = {}
    for denomination, count in denomination_count.items():
        if count > 0:
            result[denomination] = count
    
    return result



def get_min_denominations(amount):
    denominations = [25, 10, 5, 1, 0.25, 0.10, 0.05, 0.01]
    result = []
    
    # Convert amount to cents to avoid floating point precision issues
    amount = round(amount * 100)
    
    for denom in denominations:
        denom = round(denom * 100)
        count = amount // denom
        amount -= count * denom
        result.append((denom / 100, count))
    
    return result

class CashDrawer:
    def __init__(self, initial_cash):
        self.cash = initial_cash.copy()  # Ensure we have a copy of the initial state

    def can_provide_change(self, amount):
        needed_change = get_min_denominations(amount)
        temp_cash = self.cash.copy()

        for denom, count in needed_change:
            if temp_cash[denom] < count:
                return False
            temp_cash[denom] -= count

        return True

    def provide_change(self, amount):
        if not self.can_provide_change(amount):
            return "Cannot provide exact change"

        needed_change = get_min_denominations(amount)
        for denom, count in needed_change:
            self.cash[denom] -= count

        return needed_change


#######################################################################################################################
# RPN Calculator

def calculate_rpn(expression):
    stack = []
    tokens = ['+', '-', '*', '/']
    for token in expression:
        if token in tokens:
            b = stack.pop()
            a = stack.pop()
            if token == '+':
                stack.append(a + b)
            elif token == '-':
                stack.append(a - b)
            elif token == '*':
                stack.append(a * b)
            elif token == '/':
                stack.append(a / b)  # Ensure float division
        else:
            stack.append(int(token))
    
    return stack[0]

#######################################################################################################################
# Calculator Generic

def calculate(expression: str) -> int:
    # Remove whitespaces and validate input
    expression = expression.replace(' ', '')
    print(expression)
    tokens = list(expression)
    total = 0
    current_number = 0
    sign = 1  # 1 means positive, -1 means negative

    i = 0
    while i < len(tokens):
        token = tokens[i]
        if token.isdigit():
            current_number = current_number * 10 + int(token)
        elif token in '+-':
            total += sign * current_number
            current_number = 0
            sign = 1 if token == '+' else -1
        i += 1
    
    # Add the last number
    total += sign * current_number
    return total

#######################################################################################################################
# Shunting yard convert to RPN

def get_precedence(op):
    precedences = {'+': 1, '-': 1, '*': 2, '/': 2, '(': 0}
    return precedences[op]

def is_operator(c):
    return c in set(['+', '-', '*', '/'])

def shunting_yard(expression):
    expression = expression.replace(' ', '')
    output = []
    operators = []
    
    i = 0
    while i < len(expression):
        c = expression[i]
        
        if c.isdigit():
            num = c
            while i + 1 < len(expression) and expression[i + 1].isdigit():
                i += 1
                num += expression[i]
            output.append(num)
        
        elif c == '(':
            operators.append(c)
        
        elif c == ')':
            while operators and operators[-1] != '(':
                output.append(operators.pop())
            operators.pop()  # Remove '(' from the stack
        
        elif is_operator(c):
            while (operators and get_precedence(operators[-1]) >= get_precedence(c)):
                output.append(operators.pop())
            operators.append(c)
        
        i += 1
    
    while operators:
        output.append(operators.pop())
    
    return output


#######################################################################################################################
# Online Search

class Node:
    def __init__(self, name, price=None, prime_eligible=None):
        self.name = name
        self.price = price
        self.prime_eligible = prime_eligible
        self.children = []

    def add_child(self, child_node):
        self.children.append(child_node)

class Graph:
    def __init__(self):
        self.root = Node("Root")

    def add_product(self, category_path, product_name, price, prime_eligible):
        current_node = self.root
        for category in category_path:
            found = False
            for child in current_node.children:
                if child.name == category:
                    current_node = child
                    found = True
                    break
            if not found:
                new_node = Node(category)
                current_node.add_child(new_node)
                current_node = new_node
        product_node = Node(product_name, price, prime_eligible)
        current_node.add_child(product_node)

    def search_by_category(self, category):
        result = []
        self._search_by_category_recursive(self.root, category, result)
        return result

    def _search_by_category_recursive(self, node, category, result):
        if node.name == category:
            self._collect_products(node, result)
        for child in node.children:
            self._search_by_category_recursive(child, category, result)

    def _collect_products(self, node, result):
        if node.price is not None:
            result.append(node)
        for child in node.children:
            self._collect_products(child, result)

    def search_by_price(self, max_price):
        result = []
        self._search_by_price_recursive(self.root, max_price, result)
        return result

    def _search_by_price_recursive(self, node, max_price, result):
        if node.price is not None and node.price <= max_price:
            result.append(node)
        for child in node.children:
            self._search_by_price_recursive(child, max_price, result)

    def search_by_category_and_price(self, category, max_price):
        result = []
        self._search_by_category_and_price_recursive(self.root, category, max_price, result)
        return result

    def _search_by_category_and_price_recursive(self, node, category, max_price, result):
        if node.name == category:
            self._collect_products_by_price(node, max_price, result)
        for child in node.children:
            self._search_by_category_and_price_recursive(child, category, max_price, result)

    def _collect_products_by_price(self, node, max_price, result):
        if node.price is not None and node.price <= max_price:
            result.append(node)
        for child in node.children:
            self._collect_products_by_price(child, max_price, result)








def main():

    two_sum = twoSum(nums=[2, 11, 9, 1, 2, 3], target=5)
    print(f"Two Sum: {two_sum}")

    conversion_rates = [
        {"from": "USD", "to": "EUR", "rate": 0.85},
        {"from": "EUR", "to": "GBP", "rate": 0.88},
        {"from": "USD", "to": "JPY", "rate": 110.0},
        {"from": "JPY", "to": "INR", "rate": 0.67},
        {"from": "INR", "to": "USD", "rate": 0.013},
    ]

    # Test cases
    def test_convert_currency():
        # Test 1: Direct conversion USD to EUR
        amount = 100
        result = convert_currency(amount, "USD", "EUR", conversion_rates)
        print(f"{amount} USD is equal to {result} EUR")  # Expected: 85.0 EUR
        
        # Test 2: Indirect conversion USD to GBP (USD -> EUR -> GBP)
        result = convert_currency(amount, "USD", "GBP", conversion_rates)
        print(f"{amount} USD is equal to {result} GBP")  # Expected: 85.0 * 0.88 = 74.8 GBP
        
        # Test 3: Indirect conversion USD to INR (USD -> JPY -> INR)
        result = convert_currency(amount, "USD", "INR", conversion_rates)
        print(f"{amount} USD is equal to {result} INR")  # Expected: 100 * 110.0 * 0.67 = 7370.0 INR
        
        # Test 4: Direct conversion INR to USD
        amount_in_inr = 10000
        result = convert_currency(amount_in_inr, "INR", "USD", conversion_rates)
        print(f"{amount_in_inr} INR is equal to {result} USD")  # Expected: 10000 * 0.013 = 130.0 USD

    test_convert_currency()

    # Example usage:
    promotions = [(1, 3), (2, 5), (4, 6), (0, 9)]
    print("Max promotions running:")
    print(max_promotions_running(promotions))  # Output: 3


    # Example grid with 'tower' and 'obstacle'
    grid = [
        ['empty', 'empty', 'empty', 'obstacle', 'empty'],
        ['empty', 'tower', 'empty', 'tower', 'empty'],
        ['empty', 'empty', 'obstacle', 'empty', 'empty'],
        ['empty', 'tower', 'empty', 'empty', 'empty'],
        ['empty', 'empty', 'empty', 'empty', 'empty'],
    ]
    # Find all reachable towers
    result = find_reachable_towers(grid)

    # Display the result
    for tower, reachable in result.items():
        print(f"Tower at {tower} can reach towers at: {reachable}")

    tiles = ['a', 'b', 'c', 'd', 'e', 'f']
    letter_scores = {'a': 1, 'b': 3, 'c': 3, 'd': 2, 'e': 1, 'f': 4}
    valid_words = {"ab", "abc", "abd", "face", "bed", "cab"}

    best_word, best_score = find_best_word(tiles, letter_scores, valid_words)
    print(f"The best word is '{best_word}' with a score of {best_score}.")

    input_strings = ['pp', 'bin', 'foo', 'top', 'cat', 'nib', 'act', 'pot']
    print(group_anagrams(input_strings))

    print(next_greater_element([1,2,3,4,5,69,7,8,9,10]))

    # Provided blocks
    blocks = [
        ['B', 'A'], ['A', 'B'], ['L', 'E'], ['E', 'B']
    ]

    # Test with word 'BABY'
    word1 = "BABY"
    result1 = can_spell_word(blocks, word1)
    print(f"Can spell '{word1}' with the blocks: {result1}")  # Expected Output: True

    # Test with word 'ABLE'
    word2 = "ABLE"
    result2 = can_spell_word(blocks, word2)
    print(f"Can spell '{word2}' with the blocks: {result2}")  # Expected Output: True

    words = ["rock", "star", "rocks", "on", "rockstar", "super", "highway", "superhighway", "high", "way"]
    result = find_compound_words(words)
    print(result)

    amount = 69.35
    result = get_minimum_currency_denomination(amount)
    print(f"The minimum number of bills and coins for {amount} is: {result}")

    initial_cash = {25: 1, 10: 1, 5: 1, 1: 1, 0.25: 1, 0.10: 1, 0.05: 0, 0.01: 1}
    drawer = CashDrawer(initial_cash)

    amount = 6.35
    if drawer.can_provide_change(amount):
        change = drawer.provide_change(amount)
        print("Change provided:")
        for denom, count in change:
            if count > 0:
                print(f"{count} x {denom}")
    else:
        print("Cannot provide exact change")


    expression = ["16", "5", "/", "2", "-"]
    result = calculate_rpn(expression)
    print(result)  # Output will be 1.2

    graph = Graph()
    graph.add_product(["Clothing", "Women", "Dresses"], "Dress1", 20, True)
    graph.add_product(["Clothing", "Men", "Shirts"], "Shirt1", 15, False)
    graph.add_product(["Electronics", "Mobile Phones"], "Phone1", 200, True)

    # Search by category
    clothing_products = graph.search_by_category("Clothing")
    print("Clothing Products:", [product.name for product in clothing_products])

    # Search by max price
    affordable_products = graph.search_by_price(30)
    print("Products under $30:", [product.name for product in affordable_products])

    # Search by category and max price
    affordable_clothing = graph.search_by_category_and_price("Clothing", 30)
    print("Affordable Clothing:", [product.name for product in affordable_clothing])

    expression = "3 + 5 - 2"
    result = calculate(expression)
    print(f"The result of the expression '{expression}' is: {result}")

    expression = "3 + 5 * ( 2 - 8 )"
    rpn = shunting_yard(expression)
    print(f"The RPN of the expression '{expression}' is: {' '.join(rpn)}")

    result = calculate_rpn(rpn)
    print(f"The result of the RPN expression '{' '.join(rpn)}' is: {result}")




if __name__ == "__main__":
    main()
