import pandas as pd
import numpy as np
import plotly.express as px

import dash
import dash_table
import dash_daq as daq
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output

app = dash.Dash(__name__)
server = app.server

#---------------------------------------------------------------

#---------------------------------------------------------------
# df['Moving Average'] = df.iloc[:].rolling(window=3).mean()
# fig = px.line(df,y=["Price","Moving Average"])


app.layout = html.Div(children=[
    html.H1(children='Price Data'),

    dcc.Graph(
        id='price-graph'
    ),

    dcc.Slider(
        id='movAvg-slider',
        value=17,
        min=0,
        max=100,
        step=1
    ),
    html.Div(id='slider-output')
])

@app.callback(
    dash.dependencies.Output('price-graph', 'figure'),
    dash.dependencies.Output('slider-output', 'children'),
    [dash.dependencies.Input('movAvg-slider', 'value')])
def update_output(value):
    df = pd.read_csv("V4P0R_data_cleaning.csv")
    df['Moving Average'] = df.iloc[:].rolling(window=value).mean()
    fig = px.line(df,y=["Price","Moving Average"])
    spectrum = np.fft.fft(df.Price)
    spectrum = np.abs(spectrum)
    return fig, ["Strongest frequency of data: " + str(min(spectrum))]

if __name__ == '__main__':
    app.run_server(debug=True)
