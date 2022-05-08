Analyzer configuration
======================

The same scheme follows for the **analyzer**. Parameters available for this
component:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``input``
     - Input data in CSV format.
     - ``str``
     - -
   * - ``output_path``
     - Output path.
     - ``str``
     - -
   * - ``prepare_data``
     - Preprocessing configuration.
     - ``dict``
     - -
   * - ``plot``
     - Plotting parameters.
     - ``dict``
     - -
   * - ``classification``
     - Parameters for classification analyses, e.g., decision trees.
     - ``dict``
     - -
   * - ``feat_importance``
     - Parameters for feature importance analyses, e.g., random forests.
     - ``dict``
     - -


``prepare_data`` parameters:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``cols``
     - Columns or dimensions to consider.
     - ``list``
     - -
   * - ``rows``
     - Values of rows to filter.
     - ``dict``
     - -
   * - ``target``
     - Dimension of interest, e.g. FLOPS.
     - ``str``
     - -
   * - ``norm``
     - Normalization of values for the target dimension: ``minmax`` or ``zscore``.
     - ``str``
     - -
   * - ``categories``
     - Dictionary containing meta-information for the categories: ``num`` (number of categories to generate statically), ``grid_search`` (use KDE and perform grid searching for bandwidth and kernel parameters), ``mode`` (if ``normal``\ , Silverman is used for KDE. If ``multimodal``\ , Sheather-Jones is used).
     - ``dict``
     - -


``plots`` parameters:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``sort``
     - Dimension to use for sorting values.
     - ``str``
     - -
   * - ``type``
     - Type of plot: relplot, scatterplot, lineplot or kdeplot.
     - ``str``
     - -
   * - ``format``
     - Output format: png, pdf, eps, ps or svg.
     - ``str``
     - -
   * - ``x_axis``
     - Dimension for the X axis.
     - ``str``
     - -
   * - ``y_axis``
     - Dimension for the Y axis.
     - ``str``
     - -
   * - ``hue``
     - Dimension to group by color.
     - ``str``
     - -
   * - ``size``
     - Dimension to group by size.
     - ``str``
     - -
   * - ``log_scale``
     - Apply logarithmic scale.
     - ``bool``
     - -

Example
-------

Imagine we have a dataset with 5 columns: ``DIM_0``, ``DIM_1``, ``DIM_2``,
``DIM_3`` and ``Cycles``. We want to filter those values where
``DIM_1=="VALUE"``, and we want to measure the impact of the rest of the
dimensions over ``Cycles``. We also want to normalize the values and create
categories as the target dimension is not discrete. We are plotting a KDE or
density plot and a scatterplot. The system also performs a classification using
a 4-depth decision tree. The possible configuration file could be as follows:

.. code-block:: yaml

  - kernel:
      input: input.csv
      output_path: .
      prepare_data:
          cols: DIM_0 DIM_2 DIM_3
          rows: { "DIM_1": "VALUE" }
          target: Cycles
          norm: True
          categories:
              enabled: True
              scaling_factor: "1"
      plot:
          density:
              enabled: True
              type: kdeplot
              format: pdf
              data: processed
              x_axis: tsc
              x_label: "Time Stamp Counter (TSC)"
              log_scale: False
              hue: tsc_cat
              cumulative: False
              hatches: True
              multiple: "stack"
              rugplot: True
              mark_centroids: True
          scatterplot:
              enabled: False
              type: scatterplot
              format: pdf
              data: processed
              x_axis: index
              y_axis: cycles
              palette: "crimson"
              hue: arch
      classification:
          type: decision_tree
          enabled: True
          config:
              max_depth: 4
              max_leaves: 10000
              proportion: True
              text_tree: False
              graph_tree: True
              orientation: "horizontal"
      feature_importance:
          type: random_forest
          enabled: True
          config:
              n_estimators: 50
              criterion: "gini"
              max_depth: 50
              n_jobs: -1
              random_state: 0

Refer to the `examples/ <https://github.com/UDC-GAC/MARTA/tree/main/examples>`_
for more elaborate examples.