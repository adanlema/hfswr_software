`timescale 1ns / 1ps

module nco_out(
    input [1:0] adc_clk_i,  // ADC clock {p,n}
    input       exp_r_io,   
    
    // DAC
    output [13:0] dac_dat_o,  // DAC combined data
    output        dac_wrt_o,  // DAC write
    output        dac_sel_o,  // DAC channel select
    output        dac_clk_o,  // DAC clock
    output        dac_rst_o,   // DAC reset
    
    output        exp_p_io,
    output        exp_n_io
    );
    
    // PLL signals
    wire                 adc_clk_in;
    wire                 pll_adc_clk;
    wire                 pll_dac_clk_1x;
    wire                 pll_dac_clk_2x;
    wire                 pll_dac_clk_2p;
    wire                 pll_locked;
    
    wire                 adc_clk;
    
    // DAC signals
    wire                    dac_clk_1x;
    wire                    dac_clk_2x;
    wire                    dac_clk_2p;
    reg                     dac_rst;
    
    //DDS
    wire m_axis_data_tvalid;
    wire [31:0] m_axis_data_tdata;
    wire m_axis_phase_tvalid;
    wire [31:0] m_axis_phase_tdata;
    
    //DAC data
    reg [13:0] dac_dat_a;
    reg [13:0] dac_dat_b;
    reg [13:0] dac_a;
    reg [13:0] dac_b;
    
    // Modulador
    wire [13:0] senial_mod;
    
    // Sincronismo
    wire sinc;
    
    // diferential clock input
    IBUFDS i_clk (.I (adc_clk_i[1]), .IB (adc_clk_i[0]), .O (adc_clk_in));  // differential clock input
    
    pll nco_pll (
      // inputs
      .clk         (adc_clk_in),  // clock
      .rstn        (exp_r_io  ),  // reset - active low
      // output clocks
      .clk_adc     (pll_adc_clk   ),  // ADC clock
      .clk_dac_1x  (pll_dac_clk_1x),  // DAC clock 125MHz
      .clk_dac_2x  (pll_dac_clk_2x),  // DAC clock 250MHz
      .clk_dac_2p  (pll_dac_clk_2p),  // DAC clock 250MHz -45DGR
      // status outputs
      .pll_locked  (pll_locked)
    );
    
    // DAC reset (active high)
    always @(posedge dac_clk_1x)
    dac_rst  <= ~exp_r_io | ~pll_locked;
    
    BUFG bufg_adc_clk    (.O (adc_clk   ), .I (pll_adc_clk   ));
    BUFG bufg_dac_clk_1x (.O (dac_clk_1x), .I (pll_dac_clk_1x));
    BUFG bufg_dac_clk_2x (.O (dac_clk_2x), .I (pll_dac_clk_2x));
    BUFG bufg_dac_clk_2p (.O (dac_clk_2p), .I (pll_dac_clk_2p));
    
    dds_compiler_0 your_instance_name (
      .aclk(adc_clk),                              // input wire aclk
      .m_axis_data_tvalid(m_axis_data_tvalid),  // output wire m_axis_data_tvalid
      .m_axis_data_tdata(m_axis_data_tdata)    // output wire [31 : 0] m_axis_data_tdata
    );
    
        always @(posedge dac_clk_1x)
    begin
      dac_a <= m_axis_data_tdata[13:0];
      dac_b <= m_axis_data_tdata[29:16];
    end
    
    // output registers + signed to unsigned (also to negative slope)
    always @(posedge dac_clk_1x)
    begin
      dac_dat_a <= {dac_a[14-1], ~dac_a[14-2:0]};
      dac_dat_b <= {dac_b[14-1], ~dac_b[14-2:0]};
    end
     
   divisor_clk gen_sinc(
    .clk(adc_clk),
    .rst(exp_r_io),
    .clk_div(sinc));
     
    modulador_bpsk modulador(
        .clk(adc_clk),
        .rst(exp_r_io),
        .sinc(sinc),
        .cod(16'h0712),
        .senial(dac_a),
        .senial_mod(senial_mod)
    );
    
    // generating ADC clock
    ODDR i_adc_clk_p ( .Q(exp_p_io), .D1(1'b1), .D2(1'b0), .C(adc_clk_in), .CE(1'b1), .R(1'b0), .S(1'b0));
    ODDR i_adc_clk_n ( .Q(exp_n_io), .D1(1'b0), .D2(1'b1), .C(adc_clk_in), .CE(1'b1), .R(1'b0), .S(1'b0));
    
    // DDR outputs
    ODDR oddr_dac_clk          (.Q(dac_clk_o), .D1(1'b0     ), .D2(1'b1     ), .C(dac_clk_2p), .CE(1'b1), .R(1'b0   ), .S(1'b0));
    ODDR oddr_dac_wrt          (.Q(dac_wrt_o), .D1(1'b0     ), .D2(1'b1     ), .C(dac_clk_2x), .CE(1'b1), .R(1'b0   ), .S(1'b0));
    ODDR oddr_dac_sel          (.Q(dac_sel_o), .D1(1'b1     ), .D2(1'b0     ), .C(dac_clk_1x), .CE(1'b1), .R(dac_rst), .S(1'b0));
    ODDR oddr_dac_rst          (.Q(dac_rst_o), .D1(dac_rst  ), .D2(dac_rst  ), .C(dac_clk_1x), .CE(1'b1), .R(1'b0   ), .S(1'b0));
    ODDR oddr_dac_dat [14-1:0] (.Q(dac_dat_o), .D1(senial_mod), .D2(dac_dat_b), .C(dac_clk_1x), .CE(1'b1), .R(dac_rst), .S(1'b0));

endmodule