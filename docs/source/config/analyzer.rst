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
