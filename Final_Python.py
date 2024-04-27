import matplotlib.pyplot as plt
import networkx as nx
class TreeNode:
    def __init__(self, name):
        self.data = name
        self.left = None
        self.right = None
        self.parent = None

    def add_left_child(self, node):
        node.parent = self
        self.left = node

    def add_right_child(self, node):
        node.parent = self
        self.right = node
    def get_level(self):
        level = 0
        p = self.parent
        while p:
            level += 1
            p = p.parent

        return level
    
    def print_tree(self, level=0):
        spaces = ' ' * level * 3
        prefix = spaces + "|__" if self.parent else ""
        print(prefix + self.data)
        # print('-' * 3 * level + self.data)  # Visit the root first (pre-order)
        if self.left:
            self.left.print_tree(level + 1)  # Then visit the left child
        if self.right:
            self.right.print_tree(level + 1)  # Then visit the right child
    def preorder(self):
        
        traversal_list = [self.data]
        # print(self.data)
        if self.left:
            traversal_list.extend(self.left.preorder())
        if self.right:
            traversal_list.extend(self.right.preorder())
        return traversal_list
    def get_tree_structure(self):
        tree_structure = {}
        if self.left:
            tree_structure[self.left.data] = self.data
            tree_structure.update(self.left.get_tree_structure())
        if self.right:
            tree_structure[self.right.data] = self.data
            tree_structure.update(self.right.get_tree_structure())
        return tree_structure

    def plot_tree(self, parent_name=None, graph=None, level=0, pos=None, width=2., vert_gap=0.4, xcenter=0.5):
        if graph is None:
            graph = plt.figure()
        if pos is None:
            pos = {self.data: (xcenter, 1 - level * vert_gap)}
        else:
            pos[self.data] = (xcenter, 1 - level * vert_gap)
        if parent_name is not None:
            graph.add_node(parent_name)
            graph.add_node(self.data)
            graph.add_edge(parent_name, self.data)
        if self.left:
            pos = self.left.plot_tree(parent_name=self.data, graph=graph, level=level + 1, pos=pos,
                                      xcenter=xcenter - width / 2, width=width / 2)
        if self.right:
            pos = self.right.plot_tree(parent_name=self.data, graph=graph, level=level + 1, pos=pos,
                                       xcenter=xcenter + width / 2, width=width / 2)
        return pos

def plot():
    tree_structure = root.get_tree_structure()
    
    # Plot the tree
    graph = nx.DiGraph()
    graph_pos = root.plot_tree(graph=graph)
    fig = plt.figure(figsize=(8, 6))  # Adjust the size as needed
    # Draw the plot
    nx.draw(graph, pos=graph_pos, with_labels=True, node_size=1000, node_color="skyblue", font_size=8, font_weight="normal")
    mng = plt.get_current_fig_manager()
    # mng.full_screen_toggle()    
    
    plt.show()    
def bfs_search(root, target):
    if root is None:
        return None, False
    queue = [(root, None)]
    while queue:
        node, parent = queue.pop(0)
        if node.data.lower() == target.lower():
            return node, True
        if node.left:
            queue.append((node.left, node))
        if node.right:
            queue.append((node.right, node))
    
    return None, False
def dfs_search(node, target):
    if node is None:
        return None, False
    
    stack = [(node, None)]
    while stack:
        current_node, parent = stack.pop()
        if current_node.data.lower() == target.lower():
            return current_node, True
        
        # Adding right child first to the stack since we want to process it after the left child
        if current_node.right:
            stack.append((current_node.right, current_node))
        if current_node.left:
            stack.append((current_node.left, current_node))
    
    return None, False
    
root = TreeNode("United States")    

def build_product_tree():
    global root

    USA = TreeNode("USA")
    Mexico = TreeNode("Mexico")
    Canada = TreeNode("Canada")
    MexicoCity = TreeNode("Mexico City")
    MexicoCity.add_left_child(TreeNode("Berlin"))
    Mexico.add_right_child(MexicoCity)
    USA.add_right_child(Mexico)
    
    toronto = TreeNode("Toronto")
    Montreal = TreeNode("Montreal")
    Paris = TreeNode("Paris")
    toronto.add_left_child(TreeNode("Vancouver"))
    Paris.add_left_child(TreeNode("London"))
    Paris.add_right_child(TreeNode("Rome"))
    Montreal.add_left_child(Paris)
    toronto.add_right_child(Montreal)
    Canada.add_left_child(toronto)
    USA.add_left_child(Canada)

    ID = TreeNode("Intermediate Destinations")
    OC = TreeNode("Other Continents")
    Europe = TreeNode("Europe")
    Germany = TreeNode("Germany")
    Asia = TreeNode("Asia")
    Frankfurt = TreeNode("Frankfurt")
    Athens = TreeNode("Athens")
    Munich = TreeNode("Munich")
    Munich.add_left_child(TreeNode("Vienna"))
    Athens.add_left_child(TreeNode("Budapest"))
    Frankfurt.add_left_child(Munich)
    Germany.add_left_child(Frankfurt)
    Europe.add_right_child(Germany)
    ID.add_left_child(Europe)
    Asia.add_right_child(Athens)
    OC.add_left_child(Asia)
    ID.add_right_child(OC)
    
    Europe.add_left_child(MexicoCity)
    Asia.add_left_child(Frankfurt)
    
    root.add_right_child(ID)
    root.add_left_child(USA)
    
if __name__ == '__main__':
    build_product_tree()
    root.print_tree()
    print("Pre-Order Traversal of the Given Tree is : " + str(root.preorder()))
    start_country = input("Enter Starting Country : ")
    target_country = input("Enter Target Country : ")
    node_BFS,found_start_country_BFS=bfs_search(root,start_country)
    if found_start_country_BFS:
        node_target_country_BFS,found_target_country_BFS=bfs_search(node_BFS,target_country)
        if found_target_country_BFS:
            print(f"{target_country.title()} found using BFS") 
        else:
            print(f"{start_country.title()} found but {target_country} not found using BFS")   
    else:
       print(f"{start_country.title()} not found using BFS") 
     
     
    node_DFS, found_start_country_DFS = dfs_search(root, start_country)
    if found_start_country_DFS:
        node_target_country_DFS, found_target_country_DFS = dfs_search(node_DFS, target_country)
        if found_target_country_DFS:
            print(f"{target_country.title()} found using DFS") 
        else:
            print(f"{start_country.title()} found but {target_country} not found using DFS")   
    else:
        print(f"{start_country.title()} not found using DFS")
    
    plot()