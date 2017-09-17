
# coding: utf-8

# In[14]:


#!/usr/bin/python3

from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.common.exceptions import ElementNotVisibleException
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
from bs4 import BeautifulSoup
import sys

# In[15]:

chrome_options = Options()
chrome_options.add_argument('--incognito')
driver = webdriver.Chrome('/usr/local/bin/chromedriver', chrome_options = chrome_options)  # Optional argument, if not specified will search
driver.get('http://www.campuspizza.ca/?page=menu')
soup = BeautifulSoup(driver.page_source, 'lxml')


# In[22]:


def scrapeCampusPizza():
    pizzas = []
    pizzaTemplate = {"name": None, "small": None, "medium": None, "large": None, "x-large": None, "ingredients": None, "keywords":[]}
    tds = []
    for tr in soup.find_all('tr'):
        innerTds = tr.find_all('td')
        for td in innerTds:
            tds.append(td)
    cheese = pizzaTemplate.copy()
    cheese["name"] = "cheese"
    cheese["small"] = float((tds[12].text)[1:])
    cheese["medium"] = float((tds[13].text)[1:])
    cheese["large"] = float((tds[14].text)[1:])
    cheese["x-large"] = float((tds[15].text)[1:])
    cheese["keywords"] = cheese["name"]
    if(cheese["ingredients"] != None ):
        cheese["keywords"].extend(cheese["ingredients"])

    #cheese is not an ingredient, ingredients remamins as none
    pizzas.append(cheese)

    anyPizza = pizzaTemplate.copy()
    anyPizza["name"] = "any"
    anyPizza["small"] = float(((tds[12].text)[1:])) + float(((tds[17].text)[1:]))
    anyPizza["medium"] = float(((tds[13].text)[1:])) + float(((tds[18].text)[1:]))
    anyPizza["large"] = float(((tds[14].text)[1:])) + float(((tds[19].text)[1:]))
    anyPizza["x-large"] = float(((tds[15].text)[1:])) + float(((tds[20].text)[1:]))
    anyPizza["ingredients"] = ["pepperoni","ham","bacon","italian sausage","chicken","tomatoes","mushrooms","pineapple","banana peppers", "green peppers","red peppers", "black olives","onion"]
    anyPizza["keywords"].extend(anyPizza["name"])
    anyPizza["keywords"].extend(anyPizza["ingredients"])
    pizzas.append(anyPizza)
    print(pizzas)
    sys.stdout.flush()
    #return(json.JSONEncoder().encode(pizzas))

if __name__ == "__main__":
    scrapeCampusPizza()
